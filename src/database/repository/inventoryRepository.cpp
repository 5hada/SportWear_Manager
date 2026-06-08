#include "inventoryRepository.h"

std::optional<Inventory> InventoryRepository::findByProductId(int productId) const
{
    const auto found = items_.find(productId);
    if (found == items_.end()) {
        return std::nullopt;
    }
    return found->second;
}

void InventoryRepository::save(const Inventory &inventory)
{
    items_[inventory.productId()] = inventory;
}

bool InventoryRepository::removeStock(int productId, int quantity)
{
    auto found = items_.find(productId);
    return found != items_.end() && found->second.remove(quantity);
}
