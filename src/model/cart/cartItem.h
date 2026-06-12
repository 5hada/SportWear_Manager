#include "model/product/product.h"

class CartItem {
    Product product_;
    int quantity_ = 0;
public:
    CartItem() = default;
    CartItem(Product product, int quantity);

    const Product &product() const;
    int quantity() const;
    int totalPrice() const;

    void setQuantity(int quantity);
};
