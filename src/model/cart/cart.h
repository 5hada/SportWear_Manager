#ifndef CART_H
#define CART_H

#include "cartItem.h"

#include <vector>

class Cart {
public:
    const std::vector<CartItem> &items() const;

    void addItem(const Product &product, int quantity);
    bool removeItem(int productId);
    void clear();
    int totalPrice() const;

private:
    std::vector<CartItem> items_;
};

#endif // CART_H
