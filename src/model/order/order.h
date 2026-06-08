#ifndef ORDER_H
#define ORDER_H

#include "delivery.h"
#include "orderItem.h"

#include <string>
#include <vector>

enum class OrderStatus {
    Created,
    Paid,
    Cancelled,
    Refunded
};

class Order {
public:
    Order() = default;
    Order(int id, int userId, std::vector<OrderItem> items, Delivery delivery = {})
        : id_(id), userId_(userId), items_(std::move(items)), delivery_(std::move(delivery))
    {
    }

    int id() const { return id_; }
    int userId() const { return userId_; }
    OrderStatus status() const { return status_; }
    const std::vector<OrderItem> &items() const { return items_; }
    const Delivery &delivery() const { return delivery_; }

    void setStatus(OrderStatus status) { status_ = status; }
    void setDelivery(Delivery delivery) { delivery_ = std::move(delivery); }

    int totalPrice() const
    {
        int total = 0;
        for (const auto &item : items_) {
            total += item.totalPrice();
        }
        return total;
    }

private:
    int id_ = 0;
    int userId_ = 0;
    OrderStatus status_ = OrderStatus::Created;
    std::vector<OrderItem> items_;
    Delivery delivery_;
};

#endif // ORDER_H
