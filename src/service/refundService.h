#ifndef REFUNDSERVICE_H
#define REFUNDSERVICE_H

#include "database/repository/orderRepository.h"
#include "database/repository/paymentRepository.h"

class RefundService {
public:
    RefundService(OrderRepository *orders, PaymentRepository *payments);

    bool refund(int orderId);

private:
    OrderRepository *orders_ = nullptr;
    PaymentRepository *payments_ = nullptr;
};

#endif // REFUNDSERVICE_H
