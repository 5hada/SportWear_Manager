#include "cartRepository.h"
#include "database/databaseManager.h"

Cart CartRepository::getCart(int userId) const {
    Cart cart;

    constexpr auto sql =
        "SELECT product_id, quantity "
        "FROM cart_items "
        "WHERE user_id = ? "
        "ORDER BY id";

    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return cart;
    }

    sqlite3_bind_int(statement, 1, userId);

    while (sqlite3_step(statement) == SQLITE_ROW) {
        cart.addItem(
            sqlite3_column_int(statement, 0),
            sqlite3_column_int(statement, 1)
        );
    }

    sqlite3_finalize(statement);
    return cart;
}

bool CartRepository::addItem(int userId, int productId, int quantity) {
    constexpr auto sql =
        "INSERT INTO cart_items (user_id, product_id, quantity) VALUES (?, ?, ?) "
        "ON CONFLICT(user_id, product_id) DO UPDATE SET quantity = quantity + excluded.quantity";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(statement, 1, userId);
    sqlite3_bind_int(statement, 2, productId);
    sqlite3_bind_int(statement, 3, quantity);
    const bool ok = sqlite3_step(statement) == SQLITE_DONE;
    sqlite3_finalize(statement);
    return ok;
}

bool CartRepository::updateItem(int userId, int productId, int quantity) {
    constexpr auto sql =
        "UPDATE cart_items "
        "SET quantity = ? "
        "WHERE user_id = ? AND product_id = ?";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int(statement, 1, quantity);
    sqlite3_bind_int(statement, 2, userId);
    sqlite3_bind_int(statement, 3, productId);

    const bool updated =
        sqlite3_step(statement) == SQLITE_DONE &&
        sqlite3_changes(database->handle()) > 0;

    sqlite3_finalize(statement);
    return updated;
}

bool CartRepository::removeItem(int userId, int productId) {
    constexpr auto sql = "DELETE FROM cart_items WHERE user_id = ? AND product_id = ?";
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

bool CartRepository::clear(int userId) {

    constexpr auto sql = "DELETE FROM cart_items WHERE user_id = ?";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(statement, 1, userId);
    const bool ok = sqlite3_step(statement) == SQLITE_DONE;
    sqlite3_finalize(statement);
    return ok;
}