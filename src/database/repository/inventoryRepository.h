#ifndef INVENTORYREPOSITORY_H
#define INVENTORYREPOSITORY_H

#include "model/product/inventory.h"

#include <map>
#include <optional>

class InventoryRepository {
public:
    std::optional<Inventory> findByProductId(int productId) const;
    void save(const Inventory &inventory);
    bool removeStock(int productId, int quantity);

private:
    std::map<int, Inventory> items_;
};

#endif // INVENTORYREPOSITORY_H
