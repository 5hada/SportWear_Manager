#include "database/databaseManager.h"
#include "model/product/receipt.h"
#include <vector>

class DataBaseManager;

class ReceiptRepository{
    DataBaseManager* database{nullptr};

public:
    ReceiptRepository(DataBaseManager* database):database(database){}

    std::vector<Receipt> findByUser(int userId) const;
    std::vector<Receipt> findById(int id) const;


    int insertReceipt(Receipt& receipt);
    bool updateReceipt(Receipt& receipt);
};