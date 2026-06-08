#ifndef ORDERITEM_H
#define ORDERITEM_H

class OrderItem {
public:
    OrderItem() = default;
    OrderItem(int productId, int quantity, int unitPrice)
        : productId_(productId), quantity_(quantity), unitPrice_(unitPrice)
    {
    }

    int productId() const { return productId_; }
    int quantity() const { return quantity_; }
    int unitPrice() const { return unitPrice_; }
    int totalPrice() const { return quantity_ * unitPrice_; }

private:
    int productId_ = 0;
    int quantity_ = 0;
    int unitPrice_ = 0;
};

#endif // ORDERITEM_H
