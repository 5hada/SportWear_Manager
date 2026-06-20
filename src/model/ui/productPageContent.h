#pragma once

#include "model/product/product.h"
#include "model/ui/pageNavigationContent.h"

#include <string>
#include <vector>

struct ProductCardContent {
    int id = -1;
    std::string name;
    std::string category;
    int price = 0;
    int stock = 0;
    std::string detail;

    ProductCardContent(const Product& product):
        id(product.getId()),
        name(product.getName()),
        category(categoryToString(product.getCategory())),
        price(product.getPrice()),
        stock(product.getStock()),
        detail(product.getDetail().empty() ? "No detail." : product.getDetail()) {}
};

struct ProductGridPageContent {
    PageNavigationContent indexData;
    std::vector<ProductCardContent> rows;

    ProductGridPageContent(PageNavigationContent indexData): indexData(indexData) {}

    ProductGridPageContent& operator<<(const ProductCardContent& row) {
        rows.push_back(row);
        return *this;
    }

    ProductGridPageContent& operator<<(const Product& product) {
        rows.emplace_back(product);
        return *this;
    }
};
