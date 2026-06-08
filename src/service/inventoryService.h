#ifndef INVENTORYSERVICE_H
#define INVENTORYSERVICE_H

#include "database/repository/inventoryRepository.h"

class InventoryService {
public:
    explicit InventoryService(InventoryRepository *inventory);

    void setStock(int productId, int quantity);
    bool removeStock(int productId, int quantity);

private:
    InventoryRepository *inventory_ = nullptr;
};

#endif // INVENTORYSERVICE_H
