#pragma once

#include "model/product/item.h"


struct CartItem: public Item{
public:
    CartItem(int id, int count)
        : Item(id, count, -1){}

    void setPrice(int price){Item::setPrice(price);}
};