#include "product.h"
#include <utility>

Product::Product(int id, std::string name, Category category, int price, int stock)
    : id_(id), name_(std::move(name)), category_(category), price_(price), stock_(stock) {}

int Product::id() const {
    return id_;
}

const std::string &Product::name() const {
    return name_;
}

Category Product::category() const {
    return category_;
}

int Product::price() const {
    return price_;
}

int Product::stock() const {
    return stock_;
}

void Product::setName(std::string name) {
    name_ = std::move(name);
}

void Product::setCategory(Category category) {
    category_ = category;
}

void Product::setPrice(int price) {
    price_ = price;
}

void Product::setStock(int stock) {
    stock_ = stock;
}

bool Product::hasStock(int count) const {
    return count > 0 && stock_ >= count;
}

bool Product::decreaseStock(int count) {
    if (!hasStock(count)) {
        return false;
    }
    stock_ -= count;
    return true;
}
