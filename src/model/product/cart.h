#pragma once

#include "cartItem.h"

class Cart {
    int userId = 0;
    CartItems items;

public:
    Cart() = default;
    Cart(int userId, CartItems& items) : userId(userId), items(items) {}
    // ~Cart();
    void setUserId(int userId) { this->userId = userId; }
    void setItems(CartItems& items) { this->items = items; }

    int getUserId() const { return userId; }
    CartItems &getItems() { return items;}
    const CartItems &getItems() const{ return items;}

    void addItem(int productId, int count);
    void addItem(CartItem item);
    // bool subItem(int productId, int count);
    // bool removeItem(int productId);
    // void clear();

    int getTotalPrice() const;
    int getTotalCount() const;
};
