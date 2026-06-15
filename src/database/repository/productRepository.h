#pragma once

#include "database/databaseManager.h"
#include "model/product/product.h"
#include <optional>
#include <vector>

class ProductRepository {
    DataBaseManager* database{nullptr};
    mutable std::vector<Product> products;

    static Product productFromStatement(sqlite3_stmt* statement);

public:
    explicit ProductRepository(DataBaseManager* database = nullptr): database(database) {}

    void setDatabase(DataBaseManager* database) {this->database = database;}

    const std::vector<Product>& findAll() const;
    std::optional<Product> findById(int id) const;

    void save(const Product& product);
    void update(const Product& product);
    bool remove(int id);
};
