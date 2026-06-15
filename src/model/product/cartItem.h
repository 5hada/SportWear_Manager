#pragma once

#include "model/product/item.h"


struct CartItem: public Item{
    bool selected = true;
public:
    CartItem(int id, int count)
        : Item(id, count, -1){}

    bool isSelected(){return selected;}


    void setPrice(int price){Item::setPrice(price);}
    void setSelected(bool isSelected){this->selected = isSelected;}
};