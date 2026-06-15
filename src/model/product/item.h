
#pragma once

struct Item{
    int id;
    int count;
    int price;

    Item(): id(-1),count(-1),price(-1){}
    Item(int id, int count, int price)
        : id(id), count(count), price(price) {}

    int getId(){return id;}
    int getCount(){return count;}
    int getPrice(){return price;}

    void setId(int id){this->id = id;}
    void setCount(int count){this->count = count;}
    void setPrice(int price){this->price = price;}
};
