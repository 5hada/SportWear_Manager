#include "orderItem.h"

OrderItem::OrderItem(int productId, int quantity, int unitPrice)
    : productId_(productId), quantity_(quantity), unitPrice_(unitPrice) {}

int OrderItem::productId() const {
    return productId_;
}

int OrderItem::quantity() const {
    return quantity_;
}

int OrderItem::unitPrice() const {
    return unitPrice_;
}

int OrderItem::totalPrice() const {
    return quantity_ * unitPrice_;
}
