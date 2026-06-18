#pragma once

#include "cartItem.h"

class Cart {
    CartItems items;

public:
    Cart() = default;
    Cart(CartItems& items) { this->items = items; }
    // ~Cart();

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
