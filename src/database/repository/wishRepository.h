#pragma once

#include "repositoryBase.h"
#include <vector>

class WishRepository: public RepositoryBase {
public:
    WishRepository(DataBaseManager* db):RepositoryBase(db) {}
    std::vector<int> findByUser(int userId) const;

    bool insert(int userId, int productId);
    bool remove(int userId, int productId);
};
