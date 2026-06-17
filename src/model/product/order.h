#pragma once

#include "orderItem.h"
#include <vector>


class Order{
    int userId;
    int totalPrice;
    std::vector<OrderItem> items;
public:
    Order(): userId(0), totalPrice(0){};
    Order(int userId, int totalPrice, std::vector<OrderItem> items): userId(userId), totalPrice(totalPrice){setItems(items);}
    // Order(int userId, int totalPrice, std::vector<OrderItem>* items): userId(userId), totalPrice(totalPrice){setItems(items);}

    int getUserId() const {return userId;}
    int getTotalPrice() const {return totalPrice;}
    const std::vector<OrderItem>& getItems() const {return items;}

    void setUserId(int userId){this->userId = userId;}
    void setTotalPrice(int newPrice){totalPrice = newPrice;}
    void setItems(std::vector<OrderItem> items){this->items = items;}
    // void setItems(std::vector<OrderItem>* items){this->items = *items;}

    void addPrice(int price){totalPrice+=price;}
    void addItem(OrderItem& item){items.emplace_back(item);}

    void clear(){userId = 0; totalPrice = 0; items.clear();}
};
