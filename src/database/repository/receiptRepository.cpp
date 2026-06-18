#include "receiptRepository.h"
#include "sqlite3.h"

std::vector<Receipt> ReceiptRepository::findByUser(int userId) const{
    std::vector<Receipt> receipts{};
    if (hasDatabase()) {
        constexpr auto sql =
            "SELECT id, user_id, used_point, total_price, ordered_at, is_canceled, canceled_at "
            "FROM receipts "
            "WHERE user_id = ? "
            "ORDER BY id";

        sqlite3_stmt* statement = nullptr;
        if (sqlOk(sql, statement)) {
            sqlite3_bind_int(statement, 1, userId);
            while (sqlite3_step(statement) == SQLITE_ROW) {
                receipts.emplace_back(receiptFromStatement(statement));
            }

            sqlite3_finalize(statement);
        }
    }
    return receipts;
}

std::optional<Receipt> ReceiptRepository::findById(int id) const{
    std::optional<Receipt> receipt = std::nullopt;
    if (hasDatabase()) {
        constexpr auto sql =
            "SELECT id, user_id, used_point, total_price, ordered_at, is_canceled, canceled_at "
            "FROM receipts "
            "WHERE id = ? "
            "ORDER BY id";

        sqlite3_stmt* statement = nullptr;
        if (!sqlOk(sql, statement)) {
            return receipt;
        }

        sqlite3_bind_int(statement, 1, id);
        while (sqlite3_step(statement) == SQLITE_ROW) {
            receipt = receiptFromStatement(statement);
        }

        sqlite3_finalize(statement);
    }
    return receipt;
}


int ReceiptRepository::insert(Receipt& receipt) {
    if (!hasDatabase()) {return -1;}
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "INSERT INTO receipts (user_id, used_point, total_price) "
        "VALUES (?, ?, ?)";

    int receiptId = -1;
    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, receipt.getUserId());
        sqlite3_bind_int(statement, 2, receipt.getPoints());
        sqlite3_bind_int(statement, 3, receipt.getPaid());

        if (sqlite3_step(statement) == SQLITE_DONE) {
            receiptId = static_cast<int>(
                sqlite3_last_insert_rowid(db->handle())
            );
        }
        sqlite3_finalize(statement);
    }
    return receiptId;
}

bool ReceiptRepository::update(Receipt& receipt) {
    if (!hasDatabase()) {return false;}
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "UPDATE receipts "
        "SET is_canceled = ? "
        "WHERE id = ?";

    if (!sqlOk(sql, statement)) {
        return false;
    }

    sqlite3_bind_int(statement, 1, receipt.getIsCanceled() ? 1 : 0);
    sqlite3_bind_int(statement, 2, receipt.getId());

    bool success = sqlite3_step(statement) == SQLITE_DONE;

    sqlite3_finalize(statement);
    return success;
}


Receipt ReceiptRepository::receiptFromStatement(sqlite3_stmt* statement) {
    return Receipt(
        sqlite3_column_int(statement, 0),
        sqlite3_column_int(statement, 1),
        {},
        sqlite3_column_int(statement, 2),
        sqlite3_column_int(statement, 3),
        columnText(statement, 4),
        sqlite3_column_int(statement, 5),
        columnText(statement, 6));
}
