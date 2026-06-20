#pragma once

#include "Item.h"


class Order {
    int userId;
    int availablePoints;
    int totalPrice;

    Items items;

    void addPrice(int price) {totalPrice+=price;}
public:
    Order(): userId(0), availablePoints(0), totalPrice(0) {};
    Order(int userId, int totalPrice, Items items): userId(userId), totalPrice(totalPrice) {
        setItems(items);
    }
    Order(int userId, int availablePoints, int totalPrice, Items items):
        userId(userId), availablePoints(availablePoints), totalPrice(totalPrice) {
        setItems(items);
    }


    int getUserId() const {return userId;}
    int getAvailablePoints() const {return availablePoints;}
    int getTotalPrice() const {return totalPrice;}
    const Items& getItems() const {return items;}

    void setUserId(int userId) {this->userId = userId;}
    void setAvailablePoints(int availablePoints) {this->availablePoints = availablePoints;}
    void setTotalPrice(int newPrice) {totalPrice = newPrice;}
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
