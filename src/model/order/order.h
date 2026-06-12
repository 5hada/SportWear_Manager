#include "delivery.h"
#include "orderItem.h"

#include <vector>

enum class OrderStatus {
    Created,
    Paid,
    Cancelled,
    Refunded
};

class Order {
    int id_ = 0;
    int userId_ = 0;
    OrderStatus status_ = OrderStatus::Created;
    std::vector<OrderItem> items_;
    Delivery delivery_;
    
public:
    Order() = default;
    Order(int id, int userId, std::vector<OrderItem> items, Delivery delivery = {});

    int id() const;
    int userId() const;
    OrderStatus status() const;
    const std::vector<OrderItem> &items() const;
    const Delivery &delivery() const;

    void setStatus(OrderStatus status);
    void setDelivery(Delivery delivery);

    int totalPrice() const;
};