#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>

enum class DeliveryStatus {
    Ready,
    Shipping,
    Delivered,
    Cancelled
};

class Delivery {
public:
    Delivery() = default;
    Delivery(std::string address, DeliveryStatus status = DeliveryStatus::Ready)
        : address_(std::move(address)), status_(status)
    {
    }

    const std::string &address() const { return address_; }
    DeliveryStatus status() const { return status_; }

    void setAddress(std::string address) { address_ = std::move(address); }
    void setStatus(DeliveryStatus status) { status_ = status; }

private:
    std::string address_;
    DeliveryStatus status_ = DeliveryStatus::Ready;
};

#endif // DELIVERY_H
