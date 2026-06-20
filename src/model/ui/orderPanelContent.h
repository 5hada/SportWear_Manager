#pragma once

#include "model/product/item.h"

#include <vector>

struct OrderRowContent {
    int productId = -1;
    int count = 0;
    int unitPrice = 0;
    int totalPrice = 0;

    OrderRowContent(const Item& item):
        productId(item.id),
        count(item.count),
        unitPrice(item.price),
        totalPrice(item.price * item.count) {}
};

struct OrderPanelContent {
    std::vector<OrderRowContent> rows;
    int totalPrice = 0;
    int availablePoints = 0;
    int maxUsablePoint = 0;
    int payment = 0;

    OrderPanelContent& operator<<(const OrderRowContent& row) {
        rows.push_back(row);
        return *this;
    }
};
