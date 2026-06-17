#include "repositoryBase.h"
#include "model/product/receipt.h"
#include <vector>
#include <optional>

class DataBaseManager;

class ReceiptRepository: public RepositoryBase{
    static Receipt receiptFromStatement(sqlite3_stmt* statement);
public:
    ReceiptRepository(DatabaseManager* db):RepositoryBase(db) {}

    std::vector<Receipt> findByUser(int userId) const;
    std::optional<Receipt> findById(int id) const;

    int insert(Receipt& receipt);
    bool update(Receipt& receipt);
};