#include "wishRepository.h"


std::vector<int> WishRepository::findByUser(int userId) const {
    std::vector<int> productIds{};
    if (!hasDatabase()){
        constexpr auto sql =
            "SELECT product_id FROM wish_items WHERE user_id = ? ORDER BY id";
        sqlite3_stmt* statement = nullptr;
        if (sqlOk(sql, statement)) {
            sqlite3_bind_int(statement, 1, userId);
            while (sqlite3_step(statement) == SQLITE_ROW) {
                productIds.push_back(sqlite3_column_int(statement, 0));
            }
            sqlite3_finalize(statement);
        }
    }
\
    return productIds;
}

std::vector<int> WishRepository::findByProduct(int productId) const {
    std::vector<int> productIds{};
    if (hasDatabase()) {
        constexpr auto sql =
            "SELECT user_id FROM wish_items WHERE product_id = ? ORDER BY id";
        sqlite3_stmt* statement = nullptr;
        if (sqlOk(sql, statement)) {
            sqlite3_bind_int(statement, 1, productId);
            while (sqlite3_step(statement) == SQLITE_ROW) {
                productIds.push_back(sqlite3_column_int(statement, 0));
            }
            sqlite3_finalize(statement);
        }
    }
    return productIds;
}

bool WishRepository::insert(int userId, int productId) {
    if (!hasDatabase()) {return false;}

    constexpr auto sql =
        "INSERT OR IGNORE INTO wish_items (user_id, product_id) VALUES (?, ?)";
    sqlite3_stmt* statement = nullptr;
    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, userId);
        sqlite3_bind_int(statement, 2, productId);
        return sqlFin(statement);
    }
    return false;
}

bool WishRepository::remove(int userId, int productId) {
    if (!hasDatabase()) {return false;}

    constexpr auto sql =
        "DELETE FROM wish_items WHERE user_id = ? AND product_id = ?";
    sqlite3_stmt* statement = nullptr;
    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, userId);
        sqlite3_bind_int(statement, 2, productId);
        return sqlFin(statement);
    }
    return false;
}
