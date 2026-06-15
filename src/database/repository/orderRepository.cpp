#include "orderRepository.h"
#include "sqlite3.h"
#include "database/databaseManager.h"


std::vector<OrderItem> OrderRepository::findById(int receiptId) const{
    std::vector<OrderItem> items;

    constexpr auto sql =
        "SELECT product_id, quantity, price_at_added "
        "FROM order_items "
        "WHERE receipt_id = ? "
        "ORDER BY id";

    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return items;
    }

    sqlite3_bind_int(statement, 1, receiptId);
    while (sqlite3_step(statement) == SQLITE_ROW) {
        items.emplace_back(
            sqlite3_column_int(statement, 0),
            sqlite3_column_int(statement, 1),
            sqlite3_column_int(statement, 2)
        );
    }

    sqlite3_finalize(statement);
    return items;
}


bool OrderRepository::insertReceipt(int receiptId, std::vector<OrderItem>& items) {
    constexpr auto sql =
        "INSERT INTO order_items "
        "(receipt_id, product_id, quantity, price_at_added) "
        "VALUES (?, ?, ?, ?)";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }

    bool success = true;

    for (OrderItem& item : items) {
        sqlite3_bind_int(statement, 1, receiptId);
        sqlite3_bind_int(statement, 2, item.getId());      // product_id
        sqlite3_bind_int(statement, 3, item.getCount());   // quantity
        sqlite3_bind_int(statement, 4, item.getPrice());   // price_at_added

        if (sqlite3_step(statement) != SQLITE_DONE) {
            success = false;
            break;
        }

        sqlite3_reset(statement);
        sqlite3_clear_bindings(statement);
    }

    sqlite3_finalize(statement);
    return success;
}