#pragma once

#include <vector>

struct OrderRowContent {
    int productId = -1;
    int count = 0;
    int unitPrice = 0;
    int totalPrice = 0;

    OrderRowContent() = default;

    OrderRowContent(int productId, int count, int unitPrice):
        productId(productId),
        count(count),
        unitPrice(unitPrice),
        totalPrice(unitPrice * count) {}
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
