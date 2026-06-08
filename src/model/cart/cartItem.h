#ifndef CARTITEM_H
#define CARTITEM_H

#include "model/product/product.h"

class CartItem {
public:
    CartItem() = default;
    CartItem(Product product, int quantity) : product_(std::move(product)), quantity_(quantity) {}

    const Product &product() const { return product_; }
    int quantity() const { return quantity_; }
    int totalPrice() const { return product_.price() * quantity_; }

    void setQuantity(int quantity) { quantity_ = quantity; }

private:
    Product product_;
    int quantity_ = 0;
};

#endif // CARTITEM_H
