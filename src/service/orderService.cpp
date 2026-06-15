#include "orderService.h"
#include "model/product/cart.h"
#include "model/product/orderItem.h"
#include "model/product/receipt.h"
#include "database/repository/receiptRepository.h"
#include "database/repository/orderRepository.h"
#include "database/repository/cartRepository.h"
#include "database/repository/productRepository.h"


Order& OrderService::makeOrder(int userId){
    clear();
    currentOrder->setUserId(userId);
    int id;
    int price;
    for(auto& item: cartRepo->findByUser(userId).getItems()){
        if(item.selected()){
            id = item.getId();
            price = productRepo->findById(id)->getPrice();
            OrderItem newItem(id, item.getCount(), price);
            currentOrder->addItem(newItem);
            currentOrder->addPrice(price);
        }
    }
    return *currentOrder;
}


bool OrderService::confirmOrder(int userId, int usedPoint){
    if(currentOrder->getUserId() != userId){return false;}
    int totalPrice = currentOrder->getTotalPrice();
    auto& items = currentOrder->getItems();
    Receipt newReceipt(userId, items, usedPoint, totalPrice);
    int receiptId = -1;
    receiptId = receiptRepo->insert(newReceipt);
    if(receiptId == -1){return false;}
    if(!orderRepo->insert(receiptId, items)){return false;}
    addPoint(userId, totalPrice);
    clear();
    return true;
}

bool OrderService::refund(int id){
    Receipt* receipt = receiptRepo->findById(id);
    if(receipt == nullptr){return false;}
    receipt->setIsCanceled(true);
    return receiptRepo->update(*receipt);
}

void OrderService::addPoint(int userId, int totalPrice, int rate){
    if(userId==1 || userId==0){return;}
    int point = totalPrice*(rate/100);
}


void OrderService::clear(){
    currentOrder->clear();
}