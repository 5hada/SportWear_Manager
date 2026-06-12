#pragma once

#include "database/databaseManager.h"
#include "model/review.h"

#include <vector>

class ReviewRepository
{
public:
    explicit ReviewRepository(DataBaseManager* database = nullptr);

    void setDatabase(DataBaseManager* database);

    const std::vector<Review>& findAll() const;
    std::vector<Review> findByProductId(int productId) const;
    void save(const Review& review);
    int nextId() const;

private:
    bool hasDatabase() const;
    static Review reviewFromStatement(sqlite3_stmt* statement);

    DataBaseManager* database{nullptr};
    mutable std::vector<Review> reviews;
};
