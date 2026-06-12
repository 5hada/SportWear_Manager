#include "cartRepository.h"

CartRepository::CartRepository(DataBaseManager* database)
    : database(database)
{
}

void CartRepository::setDatabase(DataBaseManager* database)
{
    this->database = database;
}

Cart& CartRepository::cartForUser(int userId)
{
    return carts.try_emplace(userId, Cart(userId)).first->second;
}

Cart CartRepository::cartForUser(int userId) const
{
    return getCart(userId);
}

Cart CartRepository::getCart(int userId) const
{
    if (!hasDatabase()) {
        const auto found = carts.find(userId);
        return found == carts.end() ? Cart(userId) : found->second;
    }

    Cart cart(userId);
    constexpr auto sql =
        "SELECT c.product_id, c.quantity, p.price "
        "FROM cart_items c "
        "JOIN products p ON p.id = c.product_id "
        "WHERE c.user_id = ? "
        "ORDER BY c.id";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return cart;
    }

    sqlite3_bind_int(statement, 1, userId);
    while (sqlite3_step(statement) == SQLITE_ROW) {
        cart.addItem(
            sqlite3_column_int(statement, 0),
            sqlite3_column_int(statement, 1),
            sqlite3_column_int(statement, 2));
    }
    sqlite3_finalize(statement);
    return cart;
}

void CartRepository::addItem(int userId, int productId, int quantity)
{
    if (!hasDatabase()) {
        cartForUser(userId).addItem(productId, quantity);
        return;
    }

    constexpr auto sql =
        "INSERT INTO cart_items (user_id, product_id, quantity) VALUES (?, ?, ?) "
        "ON CONFLICT(user_id, product_id) DO UPDATE SET quantity = quantity + excluded.quantity";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return;
    }
    sqlite3_bind_int(statement, 1, userId);
    sqlite3_bind_int(statement, 2, productId);
    sqlite3_bind_int(statement, 3, quantity);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
}

bool CartRepository::removeItem(int userId, int productId)
{
    if (!hasDatabase()) {
        return cartForUser(userId).removeItem(productId);
    }

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

void CartRepository::clear(int userId)
{
    if (!hasDatabase()) {
        cartForUser(userId).clear();
        return;
    }

    constexpr auto sql = "DELETE FROM cart_items WHERE user_id = ?";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return;
    }
    sqlite3_bind_int(statement, 1, userId);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
}

bool CartRepository::hasDatabase() const
{
    return database != nullptr && database->isOpen();
}
