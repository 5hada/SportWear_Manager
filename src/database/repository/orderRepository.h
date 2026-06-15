
#include "model/product/orderItem.h"
#include <vector>

class DataBaseManager;

class OrderRepository{
    DataBaseManager* database{nullptr};

public:
    OrderRepository(DataBaseManager* database):database(database){}

    std::vector<OrderItem> findById(int receiptId) const;


    bool insertReceipt(int receiptId, std::vector<OrderItem>& items);
};