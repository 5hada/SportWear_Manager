#ifndef CARTITEM_H
#define CARTITEM_H

#include "model/product/product.h"

class CartItem {
public:
    CartItem() = default;
    CartItem(Product product, int quantity);

    const Product &product() const;
    int quantity() const;
    int totalPrice() const;

    void setQuantity(int quantity);

private:
    Product product_;
    int quantity_ = 0;
};

#endif // CARTITEM_H
