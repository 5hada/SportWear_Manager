#include "model/product/inventory.h"
#include <map>
#include <optional>

class InventoryRepository {
    std::map<int, Inventory> items_;
    
public:
    std::optional<Inventory> findByProductId(int productId) const;
    void save(const Inventory &inventory);
    bool removeStock(int productId, int quantity);
};
