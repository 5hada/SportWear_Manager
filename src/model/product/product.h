#pragma once
#pragma once

#include "category.h"
#include "productItem.h"
#include <string>

class Product {
    ProductItem item;
    std::string name;
    std::string detail;
    Category category = Category::Unknown;

public:
    Product(ProductItem item, std::string name, Category category)
        : item(item), name(std::move(name)), category(category) {}
    Product(int count, int price, std::string name, Category category)
        : item(count, price), name(std::move(name)), category(category) {}

    int getId() const { return item.id; }
    const std::string &getName() const { return name; }
    const std::string &getDetail() const{ return detail; }
    Category getCategory() const{ return category; }
    int getPrice() const{ return item.price; }
    int getStock() const{ return item.count; }

    void setName(std::string name) { this->name = name; }
    void setDetail(std::string detail) { this->detail = detail;}
    void setCategory(Category category) { this->category = category; }
    void setPrice(int price) { this->item.price = price; }
    void setStock(int stock) { this->item.count = stock; }

    bool hasStock(int count) const;
    bool decreaseStock(int count);
    void increaseStock(int count);
};