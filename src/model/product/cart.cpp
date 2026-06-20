#include "cart.h"


void Cart::addItem(int productId, int count) {
    items.emplace_back(productId, count);
}

void Cart::addItem(CartItem item) {
    items.emplace_back(item);
}



int Cart::getTotalPrice() const {
    int total = 0;
    for (const auto &item : items) {
        total += (item.price*item.count);
    }
    return total;
}


int Cart::getTotalCount() const {
    int total = 0;
    for (const auto& item : items) {
        total += item.count;
    }
    return total;
}
