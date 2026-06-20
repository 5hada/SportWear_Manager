#pragma once

#include "model/ui/pageNavigationContent.h"

#include <string>
#include <vector>
#include <utility>

struct CartRowContent {
    int productId = -1;
    std::string name;
    int count = 0;
    int unitPrice = 0;
    int totalPrice = 0;
    bool selected = false;

    CartRowContent() = default;
    CartRowContent(int productId, std::string name, int count, int unitPrice, bool selected):
        productId(productId),
        name(std::move(name)),
        count(count),
        unitPrice(unitPrice),
        totalPrice(unitPrice * count),
        selected(selected) {}
};

struct CartPageContent {
    PageNavigationContent indexData;
    std::vector<CartRowContent> rows;
    int totalCount = 0;
    int totalPrice = 0;

    CartPageContent(PageNavigationContent indexData): indexData(indexData) {}

    CartPageContent& operator<<(const CartRowContent& row) {
        rows.push_back(row);
        return *this;
    }
};
