#include "productRepository.h"

namespace {
constexpr auto selectProductColumns = "id, name, category, price, stock, detail";

std::string columnText(sqlite3_stmt* statement, int column) {
    const auto* text = sqlite3_column_text(statement, column);
    return text == nullptr ? std::string() : reinterpret_cast<const char*>(text);
}
}

const std::vector<Product>& ProductRepository::findAll() const {
    products.clear();
    const std::string sql = std::string("SELECT ") + selectProductColumns + " FROM products ORDER BY id";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        return products;
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {
        products.push_back(productFromStatement(statement));
    }
    sqlite3_finalize(statement);
    return products;
}

std::optional<Product> ProductRepository::findById(int id) const {

    const std::string sql = std::string("SELECT ") + selectProductColumns + " FROM products WHERE id = ?";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }

    sqlite3_bind_int(statement, 1, id);
    std::optional<Product> result;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        result = productFromStatement(statement);
    }
    sqlite3_finalize(statement);
    return result;
}

void ProductRepository::save(const Product& product) {
    sqlite3_stmt* statement = nullptr;
    if (product.getId() > 0) {
        constexpr auto sql =
            "INSERT INTO products (id, name, category, price, stock, detail) VALUES (?, ?, ?, ?, ?, ?) "
            "ON CONFLICT(id) DO UPDATE SET name = excluded.name, category = excluded.category, "
            "price = excluded.price, stock = excluded.stock, detail = excluded.detail";
        if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
            return;
        }
        sqlite3_bind_int(statement, 1, product.getId());
        sqlite3_bind_text(statement, 2, product.getName().c_str(), -1, SQLITE_TRANSIENT);
        const auto category = categoryToString(product.getCategory());
        sqlite3_bind_text(statement, 3, category.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(statement, 4, product.getPrice());
        sqlite3_bind_int(statement, 5, product.getStock());
        sqlite3_bind_text(statement, 6, product.getDetail().c_str(), -1, SQLITE_TRANSIENT);
    } else {
        constexpr auto sql = "INSERT INTO products (name, category, price, stock, detail) VALUES (?, ?, ?, ?, ?)";
        if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
            return;
        }
        sqlite3_bind_text(statement, 1, product.getName().c_str(), -1, SQLITE_TRANSIENT);
        const auto category = categoryToString(product.getCategory());
        sqlite3_bind_text(statement, 2, category.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(statement, 3, product.getPrice());
        sqlite3_bind_int(statement, 4, product.getStock());
        sqlite3_bind_text(statement, 5, product.getDetail().c_str(), -1, SQLITE_TRANSIENT);
    }

    sqlite3_step(statement);
    sqlite3_finalize(statement);
}

void ProductRepository::update(const Product& product) {

    for (auto& stored : products) {
        if (stored.getId() == product.getId()) {
            stored = product;
            return;
        }
    }
    products.push_back(product);
}

bool ProductRepository::remove(int id) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql = "DELETE FROM products WHERE id = ?";
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(statement, 1, id);
    const bool removed = sqlite3_step(statement) == SQLITE_DONE && sqlite3_changes(database->handle()) > 0;
    sqlite3_finalize(statement);
    return removed;
}

Product ProductRepository::productFromStatement(sqlite3_stmt* statement)
{
    Product product(
        ProductItem{sqlite3_column_int(statement, 0), sqlite3_column_int(statement, 4), sqlite3_column_int(statement, 3)},
        columnText(statement, 1),
        categoryFromString(columnText(statement, 2)));
    product.setDetail(columnText(statement, 5));
    return product;
}