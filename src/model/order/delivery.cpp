#include "delivery.h"

#include <utility>

Delivery::Delivery(std::string address, DeliveryStatus status)
    : address_(std::move(address)), status_(status)
{
}

const std::string &Delivery::address() const
{
    return address_;
}

DeliveryStatus Delivery::status() const
{
    return status_;
}

void Delivery::setAddress(std::string address)
{
    address_ = std::move(address);
}

void Delivery::setStatus(DeliveryStatus status)
{
    status_ = status;
}
