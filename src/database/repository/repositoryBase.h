#pragma once

#include "database/databaseManager.h"


class RepositoryBase{
protected:
    DatabaseManager* db{nullptr};


    static std::string columnText(sqlite3_stmt* statement, int column) {
        const auto* text = sqlite3_column_text(statement, column);
        return text == nullptr ? std::string() : reinterpret_cast<const char*>(text);
    }

    static int sqlBindText(sqlite3_stmt* statement, int index, const std::string& text){
        return sqlite3_bind_text(statement, index, text.c_str(), -1, SQLITE_TRANSIENT);
    }

    bool hasDatabase() const {
        return db != nullptr && db->isOpen();
    }

    bool sqlOk(const char* const sql, sqlite3_stmt*& statement) const{
        if (!hasDatabase()) {
            return false;
        }
        return sqlite3_prepare_v2(db->handle(), sql, -1, &statement, nullptr) == SQLITE_OK;
    }

    const bool sqlFin(sqlite3_stmt* statement) const{    //insert update delete
        if (!hasDatabase()) {
            sqlite3_finalize(statement);
            return false;
        }
        const bool changed = sqlite3_step(statement) == SQLITE_DONE && sqlite3_changes(db->handle()) > 0;
        sqlite3_finalize(statement);
        return changed;
    }
public:
    explicit RepositoryBase(DatabaseManager* db): db(db){}

    void setDatabase(DatabaseManager* db) {this->db = db;}

    bool beginTransaction() const {
        return hasDatabase() && db->execute("BEGIN TRANSACTION");
    }

    bool commitTransaction() const {
        return hasDatabase() && db->execute("COMMIT");
    }

    bool rollbackTransaction() const {
        return hasDatabase() && db->execute("ROLLBACK");
    }
};
