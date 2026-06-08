#ifndef USER_H
#define USER_H

#include "model/order/receipt.h"
#include "userBase.h"

#include <vector>

class User : public UserBase {
public:
    User() = default;
    User(int id, std::string name, std::string password, int point = 0);

    int point() const;
    const std::vector<Receipt> &receipts() const;

    void addPoint(int point);
    bool usePoint(int point);

    void addReceipt(const Receipt &receipt);

private:
    int point_ = 0;
    std::vector<Receipt> receipts_;
};

#endif // USER_H
