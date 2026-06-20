#include "orderRepository.h"


Items OrderRepository::findById(int receiptId) const{
    Items items;
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "SELECT product_id, count, price_at_added "
        "FROM order_items "
        "WHERE receipt_id = ? "
        "ORDER BY id";

    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, receiptId);
        while (sqlite3_step(statement) == SQLITE_ROW) {
            items.emplace_back(orderItemFromStatement(statement));
        }
        sqlite3_finalize(statement);
    }
    return items;
}


bool OrderRepository::insert(int receiptId, Items items) const {
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "INSERT INTO order_items "
        "(receipt_id, product_id, count, price_at_added) "
        "VALUES (?, ?, ?, ?)";

    bool success = true;
    if (!sqlOk(sql, statement)) {
        return false;
    }
    for (Item& item : items) {
        sqlite3_bind_int(statement, 1, receiptId);
        sqlite3_bind_int(statement, 2, item.getId());      // product_id
        sqlite3_bind_int(statement, 3, item.getCount());   // count
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

Item OrderRepository::orderItemFromStatement(sqlite3_stmt* statement){
    return Item(            
            sqlite3_column_int(statement, 0),
            sqlite3_column_int(statement, 1),
            sqlite3_column_int(statement, 2)
        );
}

