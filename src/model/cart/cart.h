#ifndef CART_H
#define CART_H

#include "cartItem.h"

#include <vector>

class Cart {
public:
    const std::vector<CartItem> &items() const { return items_; }

    void addItem(const Product &product, int quantity)
    {
        for (auto &item : items_) {
            if (item.product().id() == product.id()) {
                item.setQuantity(item.quantity() + quantity);
                return;
            }
        }
        items_.emplace_back(product, quantity);
    }

    bool removeItem(int productId)
    {
        const auto originalSize = items_.size();
        items_.erase(std::remove_if(items_.begin(), items_.end(), [productId](const CartItem &item) {
                         return item.product().id() == productId;
                     }),
                     items_.end());
        return items_.size() != originalSize;
    }

    void clear() { items_.clear(); }

    int totalPrice() const
    {
        int total = 0;
        for (const auto &item : items_) {
            total += item.totalPrice();
        }
        return total;
    }

private:
    std::vector<CartItem> items_;
};

#endif // CART_H
