#include "order.h"

#include <utility>

Order::Order(int id, int userId, std::vector<OrderItem> items, Delivery delivery)
    : id_(id), userId_(userId), items_(std::move(items)), delivery_(std::move(delivery))
{
}

int Order::id() const
{
    return id_;
}

int Order::userId() const
{
    return userId_;
}

OrderStatus Order::status() const
{
    return status_;
}

const std::vector<OrderItem> &Order::items() const
{
    return items_;
}

const Delivery &Order::delivery() const
{
    return delivery_;
}

void Order::setStatus(OrderStatus status)
{
    status_ = status;
}

void Order::setDelivery(Delivery delivery)
{
    delivery_ = std::move(delivery);
}

int Order::totalPrice() const
{
    int total = 0;
    for (const auto &item : items_) {
        total += item.totalPrice();
    }
    return total;
}
