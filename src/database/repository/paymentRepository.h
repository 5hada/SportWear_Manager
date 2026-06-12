#include <map>

enum class PaymentStatus {
    Pending,
    Paid,
    Refunded
};

class PaymentRepository {
    std::map<int, PaymentStatus> payments_;

public:
    void saveStatus(int orderId, PaymentStatus status);
    PaymentStatus status(int orderId) const;
};
