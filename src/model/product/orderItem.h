#pragma once
#include "model/product/item.h"

struct OrderItem: public Item{
    OrderItem(int id, int count, int price):Item(id,count, price){}

};