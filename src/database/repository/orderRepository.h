#include "repositoryBase.h"

#include "model/product/item.h"


class OrderRepository: public RepositoryBase {
    static Item orderItemFromStatement(sqlite3_stmt* statement);
public:
    OrderRepository(DatabaseManager* db):RepositoryBase(db){}


    Items findById(int receiptId) const;


    bool insert(int receiptId, Items items) const;
};