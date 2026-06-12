#include "model/order/order.h"
#include <optional>
#include <vector>

class OrderRepository {
    std::vector<Order> orders_;

public:
    const std::vector<Order> &findAll() const;
    std::optional<Order> findById(int id) const;
    std::vector<Order> findByUserId(int userId) const;
    void save(const Order &order);
    int nextId() const;
};
