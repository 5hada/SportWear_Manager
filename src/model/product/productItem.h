#pragma once

#include "model/product/item.h"


struct ProductItem: public Item{
    ProductItem(): Item() {}
    ProductItem(int id,int count, int price)
        : Item(id, count, price){}
    ProductItem(int count, int price)
        : Item(-1, count, price){}
    ProductItem(Item item)
        : Item(item){}

};