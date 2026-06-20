#pragma once

#include "repositoryBase.h"

#include "model/product/cart.h"

class CartRepository: public RepositoryBase {
    static CartItem cartItemFromStatement(sqlite3_stmt* statement);
public:
    CartRepository(DatabaseManager* db): RepositoryBase(db){}

    Cart findByUser(int userId) const;
    CartItem findByProduct(int userId, int productId) const;

    bool insert(int userId, int productId, int count, bool isSelected);
    bool update(int userId, int productId, int count, bool isSelected);
    bool updateCount(int userId, int productId, int count);
    bool updateSelected(int userId, int productId, bool isSelected);
    bool remove(int userId, int productId);
    bool removeSelected(int userId);

    bool clear(int userId);
};
