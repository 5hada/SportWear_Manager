#ifndef INVENTORYSERVICE_H
#define INVENTORYSERVICE_H

#include "database/repository/inventoryRepository.h"

class InventoryService {
public:
    explicit InventoryService(InventoryRepository *inventory) : inventory_(inventory) {}

    void setStock(int productId, int quantity)
    {
        if (inventory_ != nullptr) {
            inventory_->save(Inventory(productId, quantity));
        }
    }

    bool removeStock(int productId, int quantity)
    {
        return inventory_ != nullptr && inventory_->removeStock(productId, quantity);
    }

private:
    InventoryRepository *inventory_ = nullptr;
};

#endif // INVENTORYSERVICE_H
