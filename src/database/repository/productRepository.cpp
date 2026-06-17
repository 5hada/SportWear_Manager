#include "productRepository.h"

std::vector<Product> ProductRepository::findAll() const {
    std::vector<Product> products;
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql = 
        "SELECT id, name, category, price, stock, detail "
        "FROM products "
        "ORDER BY id ";

    if (sqlOk(sql, statement)) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            products.push_back(productFromStatement(statement));
        }
        sqlite3_finalize(statement);
    }
    return products;
}

std::optional<Product> ProductRepository::findById(int id) const {
    std::optional<Product> product;
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql = 
    "SELECT id, name, category, price, stock, detail "
    "FROM products "
    "WHERE id = ? ";
    
    if (!sqlOk(sql, statement)) {
        return std::nullopt;
    }

    sqlite3_bind_int(statement, 1, id);
    if (sqlite3_step(statement) == SQLITE_ROW) {
        product = productFromStatement(statement);
    }
    sqlite3_finalize(statement);
    return product;
}

bool ProductRepository::insert(const Product& product) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "INSERT INTO products (name, category, price, stock, detail) "
        "VALUES (?, ?, ?, ?, ?)";

    if (sqlOk(sql, statement)) {
        sqlBindText(statement, 1, product.getName());
        const auto category = categoryToString(product.getCategory());
        sqlBindText(statement, 2, category);
        sqlite3_bind_int(statement, 3, product.getPrice());
        sqlite3_bind_int(statement, 4, product.getStock());
        sqlBindText(statement, 5, product.getDetail());
        return sqlFin(statement);
    }
    return false;
}

bool ProductRepository::update(const Product& product) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "UPDATE products "
        "SET name = ?, category = ?, price = ?, stock = ?, detail = ? "
        "WHERE id = ?";

    if (sqlOk(sql, statement)) {
        sqlBindText(statement, 1, product.getName());
        const auto category = categoryToString(product.getCategory());
        sqlBindText(statement, 2, category);
        sqlite3_bind_int(statement, 3, product.getPrice());
        sqlite3_bind_int(statement, 4, product.getStock());
        sqlBindText(statement, 5, product.getDetail());
        sqlite3_bind_int(statement, 6, product.getId());
        return sqlFin(statement);
    }

    return false;
}

bool ProductRepository::remove(int id) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "DELETE FROM products WHERE id = ?";
    if (!sqlOk(sql, statement)) {
        return false;
    }
    sqlite3_bind_int(statement, 1, id);
    return sqlFin(statement);
}

Product ProductRepository::productFromStatement(sqlite3_stmt* statement) {
    Product product(
        Item{sqlite3_column_int(statement, 0), sqlite3_column_int(statement, 4), sqlite3_column_int(statement, 3)},
        columnText(statement, 1),
        categoryFromString(columnText(statement, 2)));
    product.setDetail(columnText(statement, 5));
    return product;
}