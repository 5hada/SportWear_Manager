#ifndef INVENTORYREPOSITORY_H
#define INVENTORYREPOSITORY_H

#include "model/product/inventory.h"

#include <map>
#include <optional>

class InventoryRepository {
public:
    std::optional<Inventory> findByProductId(int productId) const
    {
        const auto found = items_.find(productId);
        if (found == items_.end()) {
            return std::nullopt;
        }
        return found->second;
    }

    void save(const Inventory &inventory) { items_[inventory.productId()] = inventory; }

    bool removeStock(int productId, int quantity)
    {
        auto found = items_.find(productId);
        return found != items_.end() && found->second.remove(quantity);
    }

private:
    std::map<int, Inventory> items_;
};

#endif // INVENTORYREPOSITORY_H
