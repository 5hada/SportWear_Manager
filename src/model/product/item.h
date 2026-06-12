
#pragma once

struct Item{
    int id = 0;
    int count = 0;
    int price = 0;

    Item() = default;
    Item(int id, int count, int price = 0)
        : id(id), count(count), price(price) {}
};
