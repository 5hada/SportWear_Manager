#pragma once

#include "database/databaseManager.h"
#include <vector>

class WishRepository {
    DataBaseManager* database{nullptr};


    bool hasDatabase() const;

public:
    explicit WishRepository(DataBaseManager* database = nullptr): database(database) {}

    void setDatabase(DataBaseManager* database) {this->database = database;}

    std::vector<int> findByUser(int userId) const;

    bool add(int userId, int productId);
    bool remove(int userId, int productId);
};
