#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H

#include "database/repository/cartRepository.h"
#include "database/repository/orderRepository.h"
#include "database/repository/paymentRepository.h"
#include "database/repository/productRepository.h"

class OrderService {
public:
    OrderService(OrderRepository *orders,
                 CartRepository *carts,
                 ProductRepository *products,
                 PaymentRepository *payments);

    std::optional<Order> checkout(int userId, const Delivery &delivery);
    std::vector<Order> ordersForUser(int userId) const;

private:
    OrderRepository *orders_ = nullptr;
    CartRepository *carts_ = nullptr;
    ProductRepository *products_ = nullptr;
    PaymentRepository *payments_ = nullptr;
};

#endif // ORDERSERVICE_H
