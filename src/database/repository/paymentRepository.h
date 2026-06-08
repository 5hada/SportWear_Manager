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
    void saveStatus(int orderId, PaymentStatus status) { payments_[orderId] = status; }

    PaymentStatus status(int orderId) const
    {
        const auto found = payments_.find(orderId);
        return found == payments_.end() ? PaymentStatus::Pending : found->second;
    }

private:
    std::map<int, PaymentStatus> payments_;
};

#endif // PAYMENTREPOSITORY_H
