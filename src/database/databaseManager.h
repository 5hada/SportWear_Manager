#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "sqlite3.h"

#include <string>

class DataBaseManager {
public:
    DataBaseManager() = default;
    explicit DataBaseManager(const std::string &path) { open(path); }

    ~DataBaseManager() { close(); }

    DataBaseManager(const DataBaseManager &) = delete;
    DataBaseManager &operator=(const DataBaseManager &) = delete;

    bool open(const std::string &path)
    {
        close();
        return sqlite3_open(path.c_str(), &db_) == SQLITE_OK;
    }

    void close()
    {
        if (db_ != nullptr) {
            sqlite3_close(db_);
            db_ = nullptr;
        }
    }

    bool isOpen() const { return db_ != nullptr; }
    sqlite3 *handle() const { return db_; }

    bool execute(const std::string &sql, std::string *errorMessage = nullptr)
    {
        char *rawError = nullptr;
        const int result = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &rawError);
        if (result != SQLITE_OK) {
            if (errorMessage != nullptr && rawError != nullptr) {
                *errorMessage = rawError;
            }
            sqlite3_free(rawError);
            return false;
        }
        return true;
    }

private:
    sqlite3 *db_ = nullptr;
};

#endif // DATABASEMANAGER_H
