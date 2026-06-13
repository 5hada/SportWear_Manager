#include "orderService.h"
#include "model/product/cart.h"
#include "model/product/receipt.h"
#include <vector>


std::map<int, std::vector<OrderItem>> OrderService::makeOrder(int userId){
    
}


bool OrderService::order(int userId, Cart cartItems, int totalPrice, int usedPoint){
    auto items = getOrderItems(cartItems);
    Receipt newReceipt(userId, items, usedPoint, totalPrice-usedPoint);

    addPoint(userId, totalPrice);
    return true;
}

std::vector<OrderItem> OrderService::getOrderItems(Cart cartItems){
    std::vector<OrderItem> orderItems;
    for(auto& item : cartItems.getItems()){
        if(item.isSelected()){
            orderItems.push_back(OrderItem(item.getId(), item.getCount(), item.getPrice()));
        }
    }
    return orderItems;
}

void OrderService::addPoint(int userId, int totalPrice, int rate){
    if(userId==1 || userId==0){return;}
    int point = totalPrice*(rate/100);

}