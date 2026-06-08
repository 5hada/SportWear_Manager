#include "cart.h"

#include <algorithm>

const std::vector<CartItem> &Cart::items() const
{
    return items_;
}

void Cart::addItem(const Product &product, int quantity)
{
    for (auto &item : items_) {
        if (item.product().id() == product.id()) {
            item.setQuantity(item.quantity() + quantity);
            return;
        }
    }
    items_.emplace_back(product, quantity);
}

bool Cart::removeItem(int productId)
{
    const auto originalSize = items_.size();
    items_.erase(std::remove_if(items_.begin(), items_.end(), [productId](const CartItem &item) {
                     return item.product().id() == productId;
                 }),
                 items_.end());
    return items_.size() != originalSize;
}

void Cart::clear()
{
    items_.clear();
}

int Cart::totalPrice() const
{
    int total = 0;
    for (const auto &item : items_) {
        total += item.totalPrice();
    }
    return total;
}
