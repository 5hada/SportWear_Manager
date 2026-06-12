#pragma once

#include "database/databaseManager.h"
#include "model/product/cart.h"

#include <map>

class CartRepository
{
public:
    explicit CartRepository(DataBaseManager* database = nullptr);

    void setDatabase(DataBaseManager* database);

    Cart& cartForUser(int userId);
    Cart cartForUser(int userId) const;
    Cart getCart(int userId) const;

    void addItem(int userId, int productId, int quantity);
    bool removeItem(int userId, int productId);
    void clear(int userId);

private:
    bool hasDatabase() const;

    DataBaseManager* database{nullptr};
    std::map<int, Cart> carts;
};
