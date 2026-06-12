#pragma once

#include "database/databaseManager.h"

#include <map>
#include <vector>

class WishRepository
{
public:
    explicit WishRepository(DataBaseManager* database = nullptr);

    void setDatabase(DataBaseManager* database);

    std::vector<int> findProductIds(int userId) const;
    void add(int userId, int productId);
    bool remove(int userId, int productId);

private:
    bool hasDatabase() const;

    DataBaseManager* database{nullptr};
    std::map<int, std::vector<int>> wishlists;
};
