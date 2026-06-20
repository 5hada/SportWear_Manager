#pragma once

#include "repositoryBase.h"

#include <vector>

using std::vector;

class WishRepository: public RepositoryBase {
public:
    WishRepository(DatabaseManager* db):RepositoryBase(db) {}
    
    vector<int> findByUser(int userId) const;
    vector<int> findByProduct(int productId) const;

    bool insert(int userId, int productId);
    bool remove(int userId, int productId);
};
