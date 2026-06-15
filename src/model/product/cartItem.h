#pragma once

#include "model/product/item.h"


struct CartItem: public Item{
    int userId = 0;
    bool isSelected = true;
public:
    CartItem(int id, int count)
        : Item(id, count, -1){}
    CartItem(int id, int count, int userId, bool isSelected)
        : Item(id, count, -1), userId(userId), isSelected(isSelected){}

    bool selected(){return isSelected;}

    void setPrice(int price){Item::setPrice(price);}
    void setSelected(bool isSelected){this->isSelected = isSelected;}
};