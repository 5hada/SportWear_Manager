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
    Delivery(std::string address, DeliveryStatus status = DeliveryStatus::Ready);

    const std::string &address() const;
    DeliveryStatus status() const;

    void setAddress(std::string address);
    void setStatus(DeliveryStatus status);

private:
    std::string address_;
    DeliveryStatus status_ = DeliveryStatus::Ready;
};

#endif // DELIVERY_H
