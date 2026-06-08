#ifndef USER_H
#define USER_H

#include "model/order/receipt.h"
#include "userBase.h"

#include <vector>

class User : public UserBase {
public:
    User() = default;
    User(int id, std::string name, std::string password, int point = 0)
        : UserBase(id, std::move(name), std::move(password)), point_(point)
    {
    }

    int point() const { return point_; }
    const std::vector<Receipt> &receipts() const { return receipts_; }

    void addPoint(int point) { point_ += point; }
    bool usePoint(int point)
    {
        if (point < 0 || point_ < point) {
            return false;
        }
        point_ -= point;
        return true;
    }

    void addReceipt(const Receipt &receipt) { receipts_.push_back(receipt); }

private:
    int point_ = 0;
    std::vector<Receipt> receipts_;
};

#endif // USER_H
