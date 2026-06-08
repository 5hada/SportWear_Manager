#ifndef ORDERREPOSITORY_H
#define ORDERREPOSITORY_H

#include "model/order/order.h"

#include <optional>
#include <vector>

class OrderRepository {
public:
    const std::vector<Order> &findAll() const { return orders_; }

    std::optional<Order> findById(int id) const
    {
        for (const auto &order : orders_) {
            if (order.id() == id) {
                return order;
            }
        }
        return std::nullopt;
    }

    std::vector<Order> findByUserId(int userId) const
    {
        std::vector<Order> result;
        for (const auto &order : orders_) {
            if (order.userId() == userId) {
                result.push_back(order);
            }
        }
        return result;
    }

    void save(const Order &order)
    {
        for (auto &stored : orders_) {
            if (stored.id() == order.id()) {
                stored = order;
                return;
            }
        }
        orders_.push_back(order);
    }

    int nextId() const { return static_cast<int>(orders_.size()) + 1; }

private:
    std::vector<Order> orders_;
};

#endif // ORDERREPOSITORY_H
