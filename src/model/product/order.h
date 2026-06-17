#pragma once

#include "Item.h"


class Order{
    int userId;
    long long availablePoints;
    long long totalPrice;

    Items items;

    void addPrice(long long price){totalPrice+=price;}
public:
    Order(): userId(0), availablePoints(0), totalPrice(0) {};
    Order(int userId, long long totalPrice, Items items): userId(userId), totalPrice(totalPrice) {
        setItems(items);
    }
    Order(int userId, long long availablePoints, long long totalPrice, Items items):
        userId(userId), availablePoints(availablePoints), totalPrice(totalPrice) {
        setItems(items);
    }


    int getUserId() const {return userId;}
    long long getAvailablePoints() const {return availablePoints;}
    long long getTotalPrice() const {return totalPrice;}
    const Items& getItems() const {return items;}

    void setUserId(int userId) {this->userId = userId;}
    void setAvailablePoints(long long availablePoints) {this->availablePoints = availablePoints;}
    void setTotalPrice(long long newPrice) {totalPrice = newPrice;}
    void setItems(Items items) {this->items = items;}

    void addItem(Item item) {
        items.emplace_back(item);
        addPrice(item.getPrice()*item.getCount());
    }

    void clear() {
        userId = 0;
        availablePoints = 0;
        totalPrice = 0;
        items.clear();
    }
};
