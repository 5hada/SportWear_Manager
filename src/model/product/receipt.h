#pragma once

#include "orderItem.h"

#include <string>
#include <vector>

class Receipt;

using Receipts = std::vector<Receipt>;
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
    std::string getCanceledAt() const {return canceledAt;}

    void setId(int id) {this->id = id;}
    void setUserId(int userId){this->userId = userId;}
    void setOrderItems(std::vector<OrderItem> items) {this->items = items;}
    void setPoints(int points){this->points = points;}
    void setPaid(int paid){this->paid = paid;}
    void setDate(std::string date){this->date = date;}
    void setIsCanceled(bool isCanceled=false){this->isCanceled = isCanceled;}
    void setCanceledAt(std::string canceledAt=""){this->canceledAt = canceledAt;}

    void setData(
        int id,
        int userId,
        std::vector<OrderItem> items,
        int point,
        int paid,
        std::string date,
        bool isCanceled = false,
        std::string canceledAt = ""
    );

    void setOrderItems(std::vector<OrderItem> items) const;
};
