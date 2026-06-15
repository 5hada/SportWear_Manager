#pragma once

#include "database/databaseManager.h"


class RepositoryBase{
protected:
    DataBaseManager* db{nullptr};


    bool hasDatabase() const {
        return db != nullptr && db->isOpen();
    }

    std::string columnText(sqlite3_stmt* statement, int column) {
        const auto* text = sqlite3_column_text(statement, column);
        return text == nullptr ? std::string() : reinterpret_cast<const char*>(text);
    }
public:
    explicit RepositoryBase(DataBaseManager* db): db(db){}

    void setDatabase(DataBaseManager* db) {this->db = db;}
};