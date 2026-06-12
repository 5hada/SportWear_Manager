#include "user.h"

#include <utility>

User::User(int id, std::string name, std::string password, int point)
    : UserBase(id, std::move(name), std::move(password)), point_(point) {}

int User::point() const {
    return point_;
}

const std::vector<Receipt> &User::receipts() const {
    return receipts_;
}

void User::addPoint(int point) {
    point_ += point;
}

bool User::usePoint(int point) {
    if (point < 0 || point_ < point) {
        return false;
    }
    point_ -= point;
    return true;
}

void User::addReceipt(const Receipt &receipt) {
    receipts_.push_back(receipt);
}
