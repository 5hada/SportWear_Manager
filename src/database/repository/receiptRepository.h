#include "repositoryBase.h"

#include "model/product/receipt.h"

#include <vector>
#include <optional>

using std::vector;
using std::optional;

class DataBaseManager;

class ReceiptRepository: public RepositoryBase{
    static Receipt receiptFromStatement(sqlite3_stmt* statement);
public:
    ReceiptRepository(DatabaseManager* db):RepositoryBase(db) {}

    vector<Receipt> findByUser(int userId) const;
    optional<Receipt> findById(int id) const;

    int insert(Receipt& receipt);
    bool update(Receipt& receipt);
};