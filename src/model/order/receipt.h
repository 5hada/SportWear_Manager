class Receipt {
    int id_ = 0;
    int price_ = 0;
    int count_ = 0;
    int point_ = 0;

public:
    Receipt() = default;
    Receipt(int id, int price, int count, int point);

    int id() const;
    int price() const;
    int count() const;
    int point() const;

    int totalPrice() const;
};