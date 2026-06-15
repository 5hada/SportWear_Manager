#pragma once

#include "repositoryBase.h"
#include "model/product/cart.h"

class CartRepository: public RepositoryBase {
    static CartItem cartItemFromStatement(sqlite3_stmt* statement);
public:
    CartRepository(DatabaseManager* db): RepositoryBase(db){}

    Cart findByUser(int userId) const;

    bool insert(int userId, int productId, bool isSelected, int quantity);
    bool update(int userId, int productId, bool isSelected, int quantity);
    bool remove(int userId, int productId);

    bool clear(int userId);
};
