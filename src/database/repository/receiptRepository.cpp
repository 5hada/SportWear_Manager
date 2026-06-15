#include "receiptRepository.h"
#include "sqlite3.h"

std::vector<Receipt> ReceiptRepository::findByUser(int userId) const{
    std::vector<Receipt> receipts;

    constexpr auto sql =
        "SELECT id, used_point, total_price, ordered_at, is_canceled, canceled_at "
        "FROM receipts "
        "WHERE user_id = ? "
        "ORDER BY id";

    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return receipts;
    }

    sqlite3_bind_int(statement, 1, userId);
    while (sqlite3_step(statement) == SQLITE_ROW) {
        std::string orderedAt =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));

        std::string canceledAt;
        if (sqlite3_column_type(statement, 5) != SQLITE_NULL) {
            canceledAt = reinterpret_cast<const char*>(sqlite3_column_text(statement, 5));
        }

        receipts.emplace_back(
            sqlite3_column_int(statement, 0),
            userId,
            std::vector<OrderItem>{},
            sqlite3_column_int(statement, 1),
            sqlite3_column_int(statement, 2),
            orderedAt,
            sqlite3_column_int(statement, 4) != 0,
            canceledAt
        );
    }

    sqlite3_finalize(statement);
    return receipts;
}


bool ReceiptRepository::insertReceipt(Receipt& receipt){
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "INSERT INTO receipts (user_id, used_point, total_price) VALUES (?, ?, ? )";

    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int(statement, 1, receipt.getUserId());
    sqlite3_bind_int(statement, 2, receipt.getPoints());
    sqlite3_bind_int(statement, 3, receipt.getPaid());

    bool success = sqlite3_step(statement) == SQLITE_DONE;

    sqlite3_finalize(statement);
    return success;
}

bool ReceiptRepository::updateReceipt(Receipt& receipt) {
    sqlite3_stmt* statement = nullptr;

    constexpr auto sql =
        "UPDATE receipts "
        "SET is_canceled = ? "
        "WHERE id = ?";

    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int(statement, 1, receipt.getIsCanceled() ? 1 : 0);
    sqlite3_bind_int(statement, 2, receipt.getId());

    bool success = sqlite3_step(statement) == SQLITE_DONE;

    sqlite3_finalize(statement);
    return success;
}