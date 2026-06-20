#pragma once

#include "Item.h"

#include <string>

class Receipt;

using std::string;
using Receipts = std::vector<Receipt>;
class Receipt {
    int id;
    int userId;
    Items items;
    int points;
    int paid;
    string date;
    bool isCanceled;
    string canceledAt;

public:
    Receipt() = default;
    Receipt(
        int id,
        int userId,
        Items items,
        int point,
        int paid,
        string date,
        bool isCanceled = false,
        string canceledAt = ""
    );
    Receipt(
        int userId,
        Items items,
        int point,
        int paid
    );
    

    int getId() const { return id; }
    int getUserId() const { return userId; }
    Items getOrderItems() const{return items;}
    int getPoints() const { return points; }
    int getPaid() const { return paid; }
    string getDate() const { return date; }
    bool getIsCanceled() const { return isCanceled; }
    string getCanceledAt() const {return canceledAt;}

    void setId(int id) {this->id = id;}
    void setUserId(int userId) {this->userId = userId;}
    void setOrderItems(Items items) {this->items = items;}
    void setPoints(int points) {this->points = points;}
    void setPaid(int paid) {this->paid = paid;}
    void setDate(string date) {this->date = date;}
    void setIsCanceled(bool isCanceled = false) {this->isCanceled = isCanceled;}
    void setCanceledAt(string canceledAt = "") {this->canceledAt = canceledAt;}

    void setData(
        int id,
        int userId,
        Items items,
        int point,
        int paid,
        string date,
        bool isCanceled = false,
        string canceledAt = ""
    );

};
