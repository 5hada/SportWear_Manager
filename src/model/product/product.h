#ifndef PRODUCT_H
#define PRODUCT_H

#include "category.h"

#include <string>

class Product {
public:
    Product() = default;
    Product(int id, std::string name, Category category, int price, int stock)
        : id_(id), name_(std::move(name)), category_(category), price_(price), stock_(stock)
    {
    }

    int id() const { return id_; }
    const std::string &name() const { return name_; }
    Category category() const { return category_; }
    int price() const { return price_; }
    int stock() const { return stock_; }

    void setName(std::string name) { name_ = std::move(name); }
    void setCategory(Category category) { category_ = category; }
    void setPrice(int price) { price_ = price; }
    void setStock(int stock) { stock_ = stock; }

    bool hasStock(int count) const { return count > 0 && stock_ >= count; }
    bool decreaseStock(int count)
    {
        if (!hasStock(count)) {
            return false;
        }
        stock_ -= count;
        return true;
    }

private:
    int id_ = 0;
    std::string name_;
    Category category_ = Category::Unknown;
    int price_ = 0;
    int stock_ = 0;
};

#endif // PRODUCT_H
