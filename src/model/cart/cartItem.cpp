#include "cartItem.h"
#include <utility>

CartItem::CartItem(Product product, int quantity)
    : product_(std::move(product)), quantity_(quantity) {}

const Product &CartItem::product() const {
    return product_;
}

int CartItem::quantity() const {
    return quantity_;
}

int CartItem::totalPrice() const {
    return product_.price() * quantity_;
}

void CartItem::setQuantity(int quantity) {
    quantity_ = quantity;
}
