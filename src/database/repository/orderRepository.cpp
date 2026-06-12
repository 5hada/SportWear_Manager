#include "orderRepository.h"

const std::vector<Order> &OrderRepository::findAll() const {
    return orders_;
}

std::optional<Order> OrderRepository::findById(int id) const {
    for (const auto &order : orders_) {
        if (order.id() == id) {
            return order;
        }
    }
    return std::nullopt;
}

std::vector<Order> OrderRepository::findByUserId(int userId) const {
    std::vector<Order> result;
    for (const auto &order : orders_) {
        if (order.userId() == userId) {
            result.push_back(order);
        }
    }
    return result;
}

void OrderRepository::save(const Order &order) {
    for (auto &stored : orders_) {
        if (stored.id() == order.id()) {
            stored = order;
            return;
        }
    }
    orders_.push_back(order);
}

int OrderRepository::nextId() const {
    return static_cast<int>(orders_.size()) + 1;
}
