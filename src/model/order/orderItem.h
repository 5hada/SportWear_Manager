class OrderItem {
    int productId_ = 0;
    int quantity_ = 0;
    int unitPrice_ = 0;

public:
    OrderItem() = default;
    OrderItem(int productId, int quantity, int unitPrice);

    int productId() const;
    int quantity() const;
    int unitPrice() const;
    int totalPrice() const;
};
