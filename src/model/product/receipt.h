#pragma once

#include "orderItem.h"

#include <string>
#include <vector>

class Receipt {
    int id;
    int userId;
    std::vector<OrderItem> items;
    int points;
    int paid;
    std::string date;
    bool isCanceled;
    std::string canceledAt;

public:
    Receipt() = default;
    Receipt(
        int id,
        int userId,
        std::vector<OrderItem> items,
        int point,
        int paid,
        std::string date,
        bool isCanceled = false,
        std::string canceledAt = ""
    );
    Receipt(
        int userId,
        std::vector<OrderItem> items,
        int point,
        int paid
    );

    int getId() const { return id; }
    int getUserId() const { return userId; }
    std::vector<OrderItem> getOrderItems() const{return items;}
    int getPoints() const { return points; }
    int getPaid() const { return paid; }
    std::string getDate() const { return date; }
    bool getIsCanceled() const { return isCanceled; }

    
    void setOrderItems(std::vector<OrderItem> items) const;
};
