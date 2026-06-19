#pragma once

#include "repositoryBase.h"
#include "model/review.h"
#include <optional>
#include <vector>

class ReviewRepository: public RepositoryBase {
    static Review reviewFromStatement(sqlite3_stmt* statement);
public:
    ReviewRepository(DatabaseManager* db): RepositoryBase(db){}

    std::vector<Review> findAll() const;
    std::optional<Review> findById(int id) const;
    std::vector<Review> findByProductId(int productId) const;
    std::vector<Review> findByUser(int userId) const;

    bool insert(const Review& review);
    bool update(const Review& review);
    bool remove(int id);

    int nextId() const;
};
