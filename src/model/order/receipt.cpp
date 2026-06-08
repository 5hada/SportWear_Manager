#include "receipt.h"

Receipt::Receipt(int id, int price, int count, int point)
    : id_(id), price_(price), count_(count), point_(point)
{
}

int Receipt::id() const
{
    return id_;
}

int Receipt::price() const
{
    return price_;
}

int Receipt::count() const
{
    return count_;
}

int Receipt::point() const
{
    return point_;
}

int Receipt::totalPrice() const
{
    return price_ * count_;
}
