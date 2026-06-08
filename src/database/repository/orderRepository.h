#ifndef ORDERREPOSITORY_H
#define ORDERREPOSITORY_H

#include "model/order/order.h"

#include <optional>
#include <vector>

class OrderRepository {
public:
    const std::vector<Order> &findAll() const;
    std::optional<Order> findById(int id) const;
    std::vector<Order> findByUserId(int userId) const;
    void save(const Order &order);
    int nextId() const;

private:
    std::vector<Order> orders_;
};

#endif // ORDERREPOSITORY_H
