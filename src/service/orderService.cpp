#include "orderService.h"

#include "pointService.h"

#include "model/product/cart.h"
#include "model/product/orderItem.h"
#include "model/product/receipt.h"

#include "database/repository/receiptRepository.h"
#include "database/repository/orderRepository.h"
#include "database/repository/cartRepository.h"
#include "database/repository/productRepository.h"

#include <optional>

Receipts OrderService::getReceipts(int userId) {
    return receiptRepo->findByUser(userId);
}


Order& OrderService::makeOrder(int userId){
    clear();
    currentOrder.setUserId(userId);
    int id;
    int price;
    for(auto& item: cartRepo->findByUser(userId).getItems()){
        if(item.selected()){
            id = item.getId();
            price = productRepo->findById(id)->getPrice();
            OrderItem newItem(id, item.getCount(), price);
            currentOrder.addItem(newItem);
            currentOrder.addPrice(price * item.getCount());
        }
    }
    return currentOrder;
}


bool OrderService::confirmOrder(int userId, int usedPoint){
    if(currentOrder.getUserId() != userId){return false;}
    int totalPrice = currentOrder.getTotalPrice();
    auto& items = currentOrder.getItems();
    Receipt newReceipt(userId, items, usedPoint, totalPrice);
    int receiptId = -1;
    receiptId = receiptRepo->insert(newReceipt);
    if(receiptId == -1){return false;}
    if(!orderRepo->insert(receiptId, items)){return false;}
    pointService->reward(userId, totalPrice);
    clear();
    return true;
}

bool OrderService::refund(int id){
    std::optional<Receipt> receipt_ = receiptRepo->findById(id);
    if (receipt_ == std::nullopt) {return false;}
    Receipt receipt = receipt_.value();
    receipt.setIsCanceled(true);
    if (receiptRepo->update(receipt)){
        return pointService->revert(receipt.getUserId(), receipt.getPoints(), receipt.getPaid());
    }
    return false;
}


void OrderService::clear(){
    currentOrder.clear();
}
