#ifndef ORDERITEM_H
#define ORDERITEM_H

class OrderItem {
public:
    OrderItem() = default;
    OrderItem(int productId, int quantity, int unitPrice);

    int productId() const;
    int quantity() const;
    int unitPrice() const;
    int totalPrice() const;

private:
    int productId_ = 0;
    int quantity_ = 0;
    int unitPrice_ = 0;
};

#endif // ORDERITEM_H
