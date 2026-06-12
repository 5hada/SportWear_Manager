#pragma once

#include "item.h"
#include <vector>

class Cart {
    int userId = 0;
    std::vector<Item> items;

public:
    Cart() = default;
    Cart(int userId) { this->userId = userId; }
    // ~Cart();

    const std::vector<Item> &getItems() const;

    void addItem(int productId, int count);
    void addItem(int productId, int count, int price);
    bool subItem(int productId, int count);
    bool removeItem(int productId);
    void clear();

    int getTotalPrice() const;
};
