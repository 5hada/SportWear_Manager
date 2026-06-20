#pragma once

#include "model/product/category.h"
#include "model/ui/pageNavigationContent.h"

#include <string>
#include <utility>
#include <vector>

struct ProductCardContent {
    int id = -1;
    std::string name;
    std::string category;
    int price = 0;
    int stock = 0;
    std::string detail;

    ProductCardContent() = default;

    ProductCardContent(int id, std::string name, std::string category, int price, int stock, std::string detail):
        id(id),
        name(std::move(name)),
        category(std::move(category)),
        price(price),
        stock(stock),
        detail(std::move(detail)) {}
};

struct ProductDetailContent {
    int id = -1;
    std::string name;
    std::string category;
    int price = 0;
    int stock = 0;
    std::string detail;
    bool wished = false;

    ProductDetailContent() = default;

    ProductDetailContent(int id, std::string name, std::string category, int price, int stock, std::string detail, bool wished):
        id(id),
        name(std::move(name)),
        category(std::move(category)),
        price(price),
        stock(stock),
        detail(std::move(detail)),
        wished(wished) {}

    ProductDetailContent& operator=(const ProductCardContent& content) {
        id = content.id;
        name = content.name;
        category = content.category;
        price = content.price;
        stock = content.stock;
        detail = content.detail;
        return *this;
    }
};

struct ProductFormContent {
    int id = 0;
    std::string name;
    Category category = Category::Top;
    int price = 0;
    int stock = 0;
    std::string detail;

    ProductFormContent() = default;

    ProductFormContent(int id, std::string name, Category category, int price, int stock, std::string detail):
        id(id),
        name(std::move(name)),
        category(category),
        price(price),
        stock(stock),
        detail(std::move(detail)) {}
};

struct ProductGridPageContent {
    PageNavigationContent indexData;
    std::vector<ProductCardContent> rows;

    ProductGridPageContent(PageNavigationContent indexData): indexData(indexData) {}

    ProductGridPageContent& operator<<(const ProductCardContent& row) {
        rows.push_back(row);
        return *this;
    }

};
