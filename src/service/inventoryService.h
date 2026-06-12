#include "database/repository/inventoryRepository.h"

class InventoryService {
    InventoryRepository *inventory_ = nullptr;
    
public:
    explicit InventoryService(InventoryRepository *inventory);

    void setStock(int productId, int quantity);
    bool removeStock(int productId, int quantity);
};
