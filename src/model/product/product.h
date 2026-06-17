#pragma once

#include <string>
#include <vector>

#include "category.h"
#include "item.h"

class Product;

using std::string;
using Products = std::vector<Product>;

class Product {
    Item item;
    string name;
    string detail;
    Category category = Category::Unknown;

public:
    Product(): item() {}
    Product(Item item, string name, Category category)
        : item(item), name(std::move(name)), category(category) {}
    // Product(int count, int price, string name, Category category)
    //     : item(count, price), name(std::move(name)), category(category) {}

    int getId() const {return item.id;}
    const string& getName() const {return name;}
    const string& getDetail() const {return detail;}
    Category getCategory() const {return category;}
    int getPrice() const {return item.price;}
    int getStock() const {return item.count;}

    void setName(string name) {this->name = name;}
    void setDetail(string detail) {this->detail = detail;}
    void setCategory(Category category) {this->category = category;}
    void setPrice(int price) {this->item.price = price;}
    void setStock(int stock) {this->item.count = stock;}

    bool hasStock(int count) const;
    bool decreaseStock(int count);
    void increaseStock(int count);
};