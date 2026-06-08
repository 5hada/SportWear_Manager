#include "orderService.h"

OrderService::OrderService(OrderRepository *orders,
                           CartRepository *carts,
                           ProductRepository *products,
                           PaymentRepository *payments)
    : orders_(orders), carts_(carts), products_(products), payments_(payments)
{
}

std::optional<Order> OrderService::checkout(int userId, const Delivery &delivery)
{
    if (orders_ == nullptr || carts_ == nullptr || products_ == nullptr || payments_ == nullptr) {
        return std::nullopt;
    }

    Cart &cart = carts_->cartForUser(userId);
    if (cart.items().empty()) {
        return std::nullopt;
    }

    std::vector<OrderItem> orderItems;
    for (const auto &cartItem : cart.items()) {
        auto product = products_->findById(cartItem.product().id());
        if (!product.has_value() || !product->decreaseStock(cartItem.quantity())) {
            return std::nullopt;
        }
        products_->save(*product);
        orderItems.emplace_back(product->id(), cartItem.quantity(), product->price());
    }

    Order order(orders_->nextId(), userId, orderItems, delivery);
    order.setStatus(OrderStatus::Paid);
    orders_->save(order);
    payments_->saveStatus(order.id(), PaymentStatus::Paid);
    cart.clear();
    return order;
}

std::vector<Order> OrderService::ordersForUser(int userId) const
{
    if (orders_ == nullptr) {
        return {};
    }
    return orders_->findByUserId(userId);
}
