#pragma once

#include "model/product/item.h"

class CartItem;

using CartItems = std::vector<CartItem>;

struct CartItem: public Item{
    bool selected = true;

public:
    CartItem(): Item() {}
    CartItem(int id, int count)
        : Item(id, count, -1){}
    CartItem(int id, int count, bool isSelected)
        : Item(id, count, -1), selected(isSelected){}

    bool isSelected() const {return selected;}

    void setPrice(int price) {Item::setPrice(price);}
    void setSelected(bool isSelected) {this->selected = isSelected;}
};
