#pragma once

#include "database/databaseManager.h"
#include "model/review.h"
#include <vector>

class ReviewRepository {
    DataBaseManager* database{nullptr};

    bool hasDatabase() const;
    static Review reviewFromStatement(sqlite3_stmt* statement);
public:
    explicit ReviewRepository(DataBaseManager* database = nullptr): database(database){}

    void setDatabase(DataBaseManager* database) {this->database = database;}

    std::vector<Review> findAll() const;
    std::vector<Review> findByProductId(int productId) const;
    std::vector<Review> findByUser(int userId) const;

    bool insert(const Review& review);
    bool update(const Review& review);
    bool remove(int id);

    int nextId() const;
};
