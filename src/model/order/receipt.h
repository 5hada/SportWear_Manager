#ifndef RECEIPT_H
#define RECEIPT_H

class Receipt {
public:
    Receipt() = default;
    Receipt(int id, int price, int count, int point)
        : id_(id), price_(price), count_(count), point_(point)
    {
    }

    int id() const { return id_; }
    int price() const { return price_; }
    int count() const { return count_; }
    int point() const { return point_; }

    int totalPrice() const { return price_ * count_; }

private:
    int id_ = 0;
    int price_ = 0;
    int count_ = 0;
    int point_ = 0;
};

#endif // RECEIPT_H
