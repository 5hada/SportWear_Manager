#pragma once

#include "database/databaseManager.h"
#include "model/product/product.h"
#include <optional>
#include <vector>

class ProductRepository
{
public:
    explicit ProductRepository(DataBaseManager* database = nullptr);

    void setDatabase(DataBaseManager* database);

    const std::vector<Product>& findAll() const;
    std::optional<Product> findById(int id) const;

    void save(const Product& product);
    void update(const Product& product);
    bool remove(int id);

private:
    bool hasDatabase() const;
    static Product productFromStatement(sqlite3_stmt* statement);

    DataBaseManager* database{nullptr};
    mutable std::vector<Product> products;
};
