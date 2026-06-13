#include "receipt.h"

Receipt::Receipt(
    int id,
    int userId, 
    std::vector<OrderItem> items,
    int points,
    int paid,
    std::string date,
    bool isCanceled
):
    id(id),
    userId(userId),
    items(items),
    points(points),
    paid(paid),
    date(date),
    isCanceled(isCanceled) {}

Receipt::Receipt(
    int userId, 
    std::vector<OrderItem> items,
    int points,
    int paid
):
    userId(userId),
    items(items),
    points(points),
    paid(paid) {}