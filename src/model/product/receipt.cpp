#include "receipt.h"
#include "orderItem.h"

Receipt::Receipt(
    int id,
    int userId, 
    std::vector<OrderItem> items,
    int points,
    int paid,
    std::string date,
    bool isCanceled,
    std::string canceledAt
):
    id(id),
    userId(userId),
    items(items),
    points(points),
    paid(paid),
    date(date),
    isCanceled(isCanceled),
    canceledAt(canceledAt) {}

Receipt::Receipt(
    int userId, 
    std::vector<OrderItem>* items,
    int points,
    int paid
):
    userId(userId),
    items(*items),
    points(points),
    paid(paid) {}



void Receipt::setOrderItems(std::vector<OrderItem> items) const{
    for(OrderItem& item: items){
        items.push_back(OrderItem(item.id, item.count, item.price));
    }
}