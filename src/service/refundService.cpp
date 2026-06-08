#include "refundService.h"

RefundService::RefundService(OrderRepository *orders, PaymentRepository *payments)
    : orders_(orders), payments_(payments)
{
}

bool RefundService::refund(int orderId)
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
