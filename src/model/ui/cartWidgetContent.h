#pragma once

#include <vector>

struct CartWidgetRowContent {
    int productId = -1;
    int count = 0;
    int unitPrice = 0;
    int totalPrice = 0;

    CartWidgetRowContent() = default;

    CartWidgetRowContent(int productId, int count, int unitPrice):
        productId(productId),
        count(count),
        unitPrice(unitPrice),
        totalPrice(unitPrice * count) {}
};

struct CartWidgetContent {
    std::vector<CartWidgetRowContent> rows;

    CartWidgetContent& operator<<(const CartWidgetRowContent& row) {
        rows.push_back(row);
        return *this;
    }

};
