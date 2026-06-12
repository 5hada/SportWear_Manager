#include "paymentRepository.h"

void PaymentRepository::saveStatus(int orderId, PaymentStatus status) {
    payments_[orderId] = status;
}

PaymentStatus PaymentRepository::status(int orderId) const {
    const auto found = payments_.find(orderId);
    return found == payments_.end() ? PaymentStatus::Pending : found->second;
}
