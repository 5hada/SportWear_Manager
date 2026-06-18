#include "receipt.h"

Receipt::Receipt(
    int id,
    int userId, 
    Items items,
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
    Items items,
    int points,
    int paid
):
    userId(userId),
    items(items),
    points(points),
    paid(paid) {}



void Receipt::setData(
    int id,
    int userId,
    Items items,
    int points,
    int paid,
    std::string date,
    bool isCanceled,
    std::string canceledAt
) {
    setId(id);
    setUserId(userId);
    setOrderItems(items);
    setPoints(points);
    setPaid(paid);
    setDate(date);
    setIsCanceled(isCanceled);
    setCanceledAt(canceledAt);
}

