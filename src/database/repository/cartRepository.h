#pragma once

#include "model/product/cart.h"

class DataBaseManager;

class CartRepository{
    DataBaseManager* database{nullptr};

public:
    explicit CartRepository(DataBaseManager* database = nullptr)
    : database(database){}

    Cart getCart(int userId) const;

    bool addItem(int userId, int productId, int quantity);
    bool updateItem(int userId, int productId, int quantity);
    bool removeItem(int userId, int productId);
    bool clear(int userId);
};
