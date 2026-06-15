#pragma once

#include "repositoryBase.h"
#include "model/product/product.h"
#include <optional>
#include <vector>

class ProductRepository: public RepositoryBase {
    static Product productFromStatement(sqlite3_stmt* statement);
public:
    ProductRepository(DatabaseManager* db): RepositoryBase(db) {}

    std::vector<Product>* findAll() const;
    std::optional<Product> findById(int id) const;

    bool insert(const Product& product);
    bool update(const Product& product);
    bool remove(int id);
};
