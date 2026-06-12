#include "inventoryService.h"

InventoryService::InventoryService(InventoryRepository *inventory) : inventory_(inventory) {}

void InventoryService::setStock(int productId, int quantity) {
    if (inventory_ != nullptr) {
        inventory_->save(Inventory(productId, quantity));
    }
}

bool InventoryService::removeStock(int productId, int quantity) {
    return inventory_ != nullptr && inventory_->removeStock(productId, quantity);
}
