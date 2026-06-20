#pragma once

#include "repositoryBase.h"

#include "model/review.h"

#include <optional>

using std::optional;

class ReviewRepository: public RepositoryBase {
    static Review reviewFromStatement(sqlite3_stmt* statement);
public:
    ReviewRepository(DatabaseManager* db): RepositoryBase(db){}

    Reviews findAll() const;
    optional<Review> findById(int id) const;
    Reviews findByProductId(int productId) const;
    Reviews findByUser(int userId) const;

    bool insert(const Review& review);
    bool update(const Review& review);
    bool remove(int id);

    int nextId() const;
};
