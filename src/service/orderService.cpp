#include "orderService.h"

#include "pointService.h"

#include "database/repository/receiptRepository.h"
#include "database/repository/orderRepository.h"
#include "database/repository/cartRepository.h"
#include "database/repository/productRepository.h"

#include "model/product/cart.h"

Receipts OrderService::getReceipts(int userId) {
    if (userId == 0) {
        Receipts receipt;
        return receipt;
    }
    Receipts receipts = receiptRepo->findByUser(userId);
    for (auto& receipt : receipts) {
        receipt.setOrderItems(orderRepo->findById(receipt.getId()));
    }
    return receipts;
}


bool OrderService::makeListOrder(int userId) {
    clear();
    currentOrder.setUserId(userId);
    currentOrderFromCart = true;
    int id;
    int price;
    Cart cart = cartRepo->findByUser(userId);
    for(auto& item: cart.getItems()){
        if(item.isSelected()){
            id = item.getId();
            auto product = productRepo->findById(id);
            if (!product.has_value()) {
                clear();
                return false;
            }
            price = product->getPrice();
            Item newItem(id, item.getCount(), price);
            currentOrder.addItem(newItem);
        }
    }
    if (currentOrder.getItems().empty()) {
        clear();
        return false;
    }
    currentOrder.setAvailablePoints(pointService->getPoint(userId));
    return true;
}

bool OrderService::makeInstantOrder(int userId, int productId) {
    clear();
    auto product = productRepo->findById(productId);
    if (!product.has_value()) {return false;}
    currentOrder.setUserId(userId);
    currentOrderFromCart = false;
    Item instantItem(productId, 1, product->getPrice());
    currentOrder.addItem(instantItem);
    currentOrder.setAvailablePoints(pointService->getPoint(userId));
    return true;
}

Order OrderService::getOrder() {
    return currentOrder;
}

Order OrderService::getClear() {
    currentOrder.clear();
    return currentOrder;
}

bool OrderService::confirmOrder(int userId, int usedPoint) {
    if(currentOrder.getUserId() != userId){return false;}
    if(currentOrder.getItems().empty()){return false;}
    int totalPrice = currentOrder.getTotalPrice();
    if (usedPoint < 0 || usedPoint > currentOrder.getAvailablePoints() || usedPoint > totalPrice) {return false;}
    const int paid = totalPrice - usedPoint;
    auto& items = currentOrder.getItems();
    Receipt newReceipt(userId, items, usedPoint, paid);

    if (!receiptRepo->beginTransaction()) {return false;}

    for (const auto& item : items) {
        auto product = productRepo->findById(item.id);
        if (!product.has_value() || !product->decreaseStock(item.count) || !productRepo->update(product.value())) {
            receiptRepo->rollbackTransaction();
            return false;
        }
    }

    int receiptId = receiptRepo->insert(newReceipt);
    if(receiptId == -1){
        receiptRepo->rollbackTransaction();
        return false;
    }
    if(!orderRepo->insert(receiptId, items)){
        receiptRepo->rollbackTransaction();
        return false;
    }
    if(currentOrderFromCart && !cartRepo->removeSelected(userId)){
        receiptRepo->rollbackTransaction();
        return false;
    }
    if(usedPoint > 0 && !pointService->handlePoint(PointAction::Sub, userId, usedPoint)) {
        receiptRepo->rollbackTransaction();
        return false;
    }
    if(!pointService->reward(userId, paid)){
        receiptRepo->rollbackTransaction();
        return false;
    }
    if(!receiptRepo->commitTransaction()){
        receiptRepo->rollbackTransaction();
        return false;
    }
    clear();
    return true;
}

bool OrderService::refund(int id, int userId) {
    std::optional<Receipt> receipt_ = receiptRepo->findById(id);
    if (receipt_ == std::nullopt) {return false;}
    Receipt receipt = receipt_.value();
    if (receipt.getUserId() != userId) {return false;}
    if (receipt.getIsCanceled()) {return false;}
    receipt.setIsCanceled(true);
    if (!receiptRepo->beginTransaction()) {return false;}
    const auto items = orderRepo->findById(receipt.getId());
    for (const auto& item : items) {
        auto product = productRepo->findById(item.id);
        if (!product.has_value()) {
            receiptRepo->rollbackTransaction();
            return false;
        }
        product->increaseStock(item.count);
        if (!productRepo->update(product.value())) {
            receiptRepo->rollbackTransaction();
            return false;
        }
    }
    if (!receiptRepo->update(receipt)){
        receiptRepo->rollbackTransaction();
        return false;
    }
    if (!pointService->revert(receipt.getUserId(), receipt.getPoints(), receipt.getPaid())) {
        receiptRepo->rollbackTransaction();
        return false;
    }
    if (!receiptRepo->commitTransaction()) {
        receiptRepo->rollbackTransaction();
        return false;
    }
    return true;
}


void OrderService::clear() {
    currentOrder.clear();
    currentOrderFromCart = false;
}
