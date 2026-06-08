#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory {
public:
    Inventory() = default;
    Inventory(int productId, int quantity) : productId_(productId), quantity_(quantity) {}

    int productId() const { return productId_; }
    int quantity() const { return quantity_; }

    void setQuantity(int quantity) { quantity_ = quantity; }
    void add(int quantity) { quantity_ += quantity; }

    bool remove(int quantity)
    {
        if (quantity < 0 || quantity_ < quantity) {
            return false;
        }
        quantity_ -= quantity;
        return true;
    }

private:
    int productId_ = 0;
    int quantity_ = 0;
};

#endif // INVENTORY_H
