#ifndef REFUNDSERVICE_H
#define REFUNDSERVICE_H

#include "database/repository/orderRepository.h"
#include "database/repository/paymentRepository.h"

class RefundService {
public:
    RefundService(OrderRepository *orders, PaymentRepository *payments)
        : orders_(orders), payments_(payments)
    {
    }

    bool refund(int orderId)
    {
        if (orders_ == nullptr || payments_ == nullptr) {
            return false;
        }
        auto order = orders_->findById(orderId);
        if (!order.has_value() || payments_->status(orderId) != PaymentStatus::Paid) {
            return false;
        }
        order->setStatus(OrderStatus::Refunded);
        orders_->save(*order);
        payments_->saveStatus(orderId, PaymentStatus::Refunded);
        return true;
    }

private:
    OrderRepository *orders_ = nullptr;
    PaymentRepository *payments_ = nullptr;
};

#endif // REFUNDSERVICE_H
