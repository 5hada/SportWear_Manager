#include <string>

enum class DeliveryStatus {
    Ready,
    Shipping,
    Delivered,
    Cancelled
};

class Delivery {
    std::string address_;
    DeliveryStatus status_ = DeliveryStatus::Ready;

public:
    Delivery() = default;
    Delivery(std::string address, DeliveryStatus status = DeliveryStatus::Ready);

    const std::string &address() const;
    DeliveryStatus status() const;

    void setAddress(std::string address);
    void setStatus(DeliveryStatus status);
};