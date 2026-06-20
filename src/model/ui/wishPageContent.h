#pragma once

#include "model/ui/pageNavigationContent.h"
#include "model/product/product.h"

#include <string>
#include <vector>
#include <utility>

using std::string;

struct WishRowContent {
    int id = -1;
    string name;
    int price = 0;
    int stock = 0;

    WishRowContent(int id, string name, int price, int stock): id(id), name(std::move(name)), price(price), stock(stock) {}
   WishRowContent(const Product& product):
        id(product.getId()),
        name(product.getName()),
        price(product.getPrice()),
        stock(product.getStock()) {}
};

struct WishPageContent{
    PageNavigationContent indexData;
    std::vector<WishRowContent> rows;

    WishPageContent(PageNavigationContent indexData): indexData(indexData) {}

    WishPageContent& operator<<(const WishRowContent& row) {
        rows.push_back(row);
        return *this;
    }

    WishPageContent& operator<<(const Product& product) {
        rows.emplace_back(product);
        return *this;
    }
};
