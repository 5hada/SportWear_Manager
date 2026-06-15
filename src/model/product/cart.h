#pragma once

#include "cartItem.h"
#include <vector>

class Cart {
    std::vector<CartItem> items;

public:
    Cart() = default;
    Cart(std::vector<CartItem>& items) { this->items = items; }
    // ~Cart();

    std::vector<CartItem> &getItems() { return items;}
    const std::vector<CartItem> &getItems() const{ return items;}

    void addItem(int productId, int count);
    void addItem(CartItem item);
    // bool subItem(int productId, int count);
    // bool removeItem(int productId);
    // void clear();

    int getTotalPrice() const;
    int getTotalCount() const;
};
