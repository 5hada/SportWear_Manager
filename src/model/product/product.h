#pragma once

#include "category.h"
#include <string>

class Product {
    int id_ = 0;
    std::string name_;
    Category category_ = Category::Unknown;
    int price_ = 0;
    int stock_ = 0;

public:
    Product() = default;
    Product(int id, std::string name, Category category, int price, int stock);

    int id() const;
    const std::string &name() const;
    Category category() const;
    int price() const;
    int stock() const;

    void setName(std::string name);
    void setCategory(Category category);
    void setPrice(int price);
    void setStock(int stock);

    bool hasStock(int count) const;
    bool decreaseStock(int count);
};