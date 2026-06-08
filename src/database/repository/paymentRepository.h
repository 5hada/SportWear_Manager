#ifndef PAYMENTREPOSITORY_H
#define PAYMENTREPOSITORY_H

#include <map>

enum class PaymentStatus {
    Pending,
    Paid,
    Refunded
};

class PaymentRepository {
public:
    void saveStatus(int orderId, PaymentStatus status);
    PaymentStatus status(int orderId) const;

private:
    std::map<int, PaymentStatus> payments_;
};

#endif // PAYMENTREPOSITORY_H
