#include "inventory.h"

Inventory::Inventory(int productId, int quantity) : productId_(productId), quantity_(quantity) {}

int Inventory::productId() const
{
    return productId_;
}

int Inventory::quantity() const
{
    return quantity_;
}

void Inventory::setQuantity(int quantity)
{
    quantity_ = quantity;
}

void Inventory::add(int quantity)
{
    quantity_ += quantity;
}

bool Inventory::remove(int quantity)
{
    if (quantity < 0 || quantity_ < quantity) {
        return false;
    }
    quantity_ -= quantity;
    return true;
}
