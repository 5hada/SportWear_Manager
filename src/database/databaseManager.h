#pragma once

#include "sqlite3.h"

#include <string>

using std::string;

class DatabaseManager {
public:
    DatabaseManager() = default;
    explicit DatabaseManager(string path) {open(path);}
    ~DatabaseManager() {close();}

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    DatabaseManager(DatabaseManager&& other) noexcept;
    DatabaseManager& operator=(DatabaseManager&& other) noexcept;

    bool open(const string& path);
    void close();
    
    bool isOpen() const {return db != nullptr;}

    sqlite3* handle() const {return db;}
    const string& lastError() const {return lastErrorMessage;}

    bool execute(const string& sql);
    bool executeFile(const string& path);
    bool initialize(const string& databasePath, const string& schemaPath);

private:
    void setErrorFromSqlite(int resultCode);

    sqlite3* db{nullptr};
    string lastErrorMessage;
};
