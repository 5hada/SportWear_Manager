#include "cartRepository.h"

Cart CartRepository::findByUser(int userId) const {
    Cart cart;
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "SELECT user_id, product_id, count, is_selected "
        "FROM cart_items "
        "WHERE user_id = ? "
        "ORDER BY id";

    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, userId);

        while (sqlite3_step(statement) == SQLITE_ROW) {
            cart.addItem(cartItemFromStatement(statement));
        }
        sqlite3_finalize(statement);
    }
    return cart;
}

CartItem CartRepository::findByProduct(int productId) const {
    CartItem item;
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "SELECT user_id, product_id, count, is_selected "
        "FROM cart_items "
        "WHERE product_id = ? "
        "ORDER BY id";

    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, productId);
        item = cartItemFromStatement(statement);
        sqlite3_finalize(statement);
    }
    return item;
}

bool CartRepository::insert(int userId, int productId, int count, bool isSelected) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "INSERT INTO cart_items (user_id, product_id, count, is_selected) "
        "VALUES (?, ?, ?, ?) ";

    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, userId);
        sqlite3_bind_int(statement, 2, productId);
        sqlite3_bind_int(statement, 3, count);
        sqlite3_bind_int(statement, 4, isSelected? 1 : 0);
        return sqlFin(statement);
    }
    return false;
}

bool CartRepository::update(int userId, int productId, int count, bool isSelected) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "UPDATE cart_items "
        "SET count = ?, is_selected = ? "
        "WHERE user_id = ? AND product_id = ?";

    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, count);
        sqlite3_bind_int(statement, 2, isSelected? 1 : 0);
        sqlite3_bind_int(statement, 3, userId);
        sqlite3_bind_int(statement, 4, productId);
        return sqlFin(statement);
    }
    return false;
}

bool CartRepository::updateCount(int userId, int productId, int count) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "UPDATE cart_items "
        "SET count = ? "
        "WHERE user_id = ? AND product_id = ?";

    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, count);
        sqlite3_bind_int(statement, 2, userId);
        sqlite3_bind_int(statement, 3, productId);
        return sqlFin(statement);
    }
    return false;
}

bool CartRepository::updateSelected(int userId, int productId, bool isSelected) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "UPDATE cart_items "
        "SET is_selected = ? "
        "WHERE user_id = ? AND product_id = ?";

    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, isSelected? 1 : 0);
        sqlite3_bind_int(statement, 2, userId);
        sqlite3_bind_int(statement, 3, productId);
        return sqlFin(statement);
    }
    return false;
}

bool CartRepository::remove(int userId, int productId) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "DELETE FROM cart_items WHERE user_id = ? AND product_id = ?";

    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, userId);
        sqlite3_bind_int(statement, 2, productId);
        return sqlFin(statement);
    }
    return false;
}

bool CartRepository::clear(int userId) {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "DELETE FROM cart_items WHERE user_id = ?";

    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, userId);
        return sqlFin(statement);
    }
    return false;
}

CartItem CartRepository::cartItemFromStatement(sqlite3_stmt* statement){
    return CartItem(
        sqlite3_column_int(statement, 1),
        sqlite3_column_int(statement, 2),
        sqlite3_column_int(statement, 0),
        sqlite3_column_int(statement, 3)
    );
}