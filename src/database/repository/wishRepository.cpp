#include "wishRepository.h"


std::vector<int> WishRepository::findByUser(int userId) const {
    if (!hasDatabase()) {return {};}

    std::vector<int> productIds;
    constexpr auto sql = "SELECT product_id FROM wish_items WHERE user_id = ? ORDER BY id";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return productIds;
    }

    sqlite3_bind_int(statement, 1, userId);
    while (sqlite3_step(statement) == SQLITE_ROW) {
        productIds.push_back(sqlite3_column_int(statement, 0));
    }
    sqlite3_finalize(statement);
    return productIds;
}

bool WishRepository::add(int userId, int productId) {
    if (!hasDatabase()) {return false;}

    constexpr auto sql =
        "INSERT OR IGNORE INTO wish_items (user_id, product_id) VALUES (?, ?)";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(statement, 1, userId);
    sqlite3_bind_int(statement, 2, productId);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
}

bool WishRepository::remove(int userId, int productId) {
    if (!hasDatabase()) {return false;}

    constexpr auto sql =
        "DELETE FROM wish_items WHERE user_id = ? AND product_id = ?";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(statement, 1, userId);
    sqlite3_bind_int(statement, 2, productId);
    const bool removed = sqlite3_step(statement) == SQLITE_DONE && sqlite3_changes(database->handle()) > 0;
    sqlite3_finalize(statement);
    return removed;
}

bool WishRepository::hasDatabase() const {
    return database != nullptr && database->isOpen();
}
