#pragma once

#include <vector>

class Item;

using Items = std::vector<Item>;

struct Item{
    int id;
    int count;
    long long price;

    Item(): id(-1),count(-1),price(-1) {}
    Item(int id, int count, long long price)
        : id(id), count(count), price(price) {}

    int getId() {return id;}
    int getCount() {return count;}
    long long getPrice() {return price;}

    void setId(int id) {this->id = id;}
    void setCount(int count) {this->count = count;}
    void setPrice(long long price) {this->price = price;}
};
