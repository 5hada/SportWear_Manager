#include "orderService.h"

#include "pointService.h"

#include "model/product/cart.h"
#include "model/product/receipt.h"

#include "database/repository/receiptRepository.h"
#include "database/repository/orderRepository.h"
#include "database/repository/cartRepository.h"
#include "database/repository/productRepository.h"

#include <optional>

Receipts OrderService::getReceipts(int userId) {
    if (userId == 0) {
        Receipts receipt;
        return receipt;
    }
    return receiptRepo->findByUser(userId);
}


bool OrderService::makeListOrder(int userId) {
    clear();
    currentOrder.setUserId(userId);
    int id, price;
    for(auto& item: cartRepo->findByUser(userId).getItems()){
        if(item.selected()){
            id = item.getId();
            price = productRepo->findById(id)->getPrice();
            Item newItem(id, item.getCount(), price);
            currentOrder.addItem(newItem);
        }
    }
    currentOrder.setAvailablePoints(pointService->getPoint(userId));
    return true;
}

bool OrderService::makeInstantOrder(int productId) {
    clear();
    if (!productRepo->findById(productId)) {return false;}
    Item instantItem(productId, 1, productRepo->findById(productId)->getPrice());
    currentOrder.addItem(instantItem);
    currentOrder.setAvailablePoints(0);
    return true;
}

Order& OrderService::getOrder() {
    return currentOrder;
}

Order& OrderService::getClear() {
    currentOrder.clear();
    return currentOrder;
}

bool OrderService::confirmOrder(int userId, int usedPoint) {
    if(currentOrder.getUserId() != userId){return false;}
    int totalPrice = currentOrder.getTotalPrice();
    auto& items = currentOrder.getItems();
    Receipt newReceipt(userId, items, usedPoint, totalPrice);
    int receiptId = -1;
    receiptId = receiptRepo->insert(newReceipt);
    if(receiptId == -1){return false;}
    if(!orderRepo->insert(receiptId, items)){return false;}
    if(!cartRepo->removeSelected(userId)){return false;}
    pointService->reward(userId, totalPrice);
    clear();
    return true;
}

bool OrderService::refund(int id, int userId) {
    std::optional<Receipt> receipt_ = receiptRepo->findById(id);
    if (receipt_ == std::nullopt) {return false;}
    Receipt receipt = receipt_.value();
    if (receipt.getUserId() != userId) {return false;}
    receipt.setIsCanceled(true);
    if (receiptRepo->update(receipt)){
        return pointService->revert(receipt.getUserId(), receipt.getPoints(), receipt.getPaid());
    }
    return false;
}


void OrderService::clear() {
    currentOrder.clear();
}
