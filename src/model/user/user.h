#include "model/order/receipt.h"
#include "userBase.h"

#include <vector>

class User : public UserBase {
    int point_ = 0;
    std::vector<Receipt> receipts_;

public:
    User() = default;
    User(int id, std::string name, std::string password, int point = 0);

    int point() const;
    const std::vector<Receipt> &receipts() const;

    void addPoint(int point);
    bool usePoint(int point);

    void addReceipt(const Receipt &receipt);
};