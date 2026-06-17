#include "repositoryBase.h"
#include "model/product/orderItem.h"
#include <vector>


class OrderRepository: public RepositoryBase {
    static OrderItem orderItemFromStatement(sqlite3_stmt* statement);
public:
    OrderRepository(DatabaseManager* db):RepositoryBase(db){}


    std::vector<OrderItem> findById(int receiptId) const;


    bool insert(int receiptId, std::vector<OrderItem> items) const;
};