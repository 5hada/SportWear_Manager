#pragma once

#include "cartItem.h"

class Cart {
    int userId = 0;
    CartItems items;

public:
    Cart(): items() {}
    Cart(int userId, CartItems& items) : userId(userId), items(items) {}

    void setUserId(int userId) { this->userId = userId; }
    void setItems(CartItems& items) { this->items = items; }

    int getUserId() const { return userId; }
    CartItems &getItems() { return items;}
    const CartItems &getItems() const{ return items;}

    void addItem(int productId, int count);
    void addItem(CartItem item);

    int getTotalPrice() const;
    int getTotalCount() const;
};
