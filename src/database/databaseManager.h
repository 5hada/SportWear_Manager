#pragma once

#include "sqlite3.h"
#include <string>

class DatabaseManager {
public:
    DatabaseManager() = default;
    explicit DatabaseManager(std::string path) {open(path);}
    ~DatabaseManager() {close();}

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    DatabaseManager(DatabaseManager&& other) noexcept;
    DatabaseManager& operator=(DatabaseManager&& other) noexcept;

    bool open(const std::string& path);
    void close();
    
    bool isOpen() const {return db != nullptr;}

    sqlite3* handle() const {return db;}
    const std::string& lastError() const {return lastErrorMessage;}

    bool execute(const std::string& sql);
    bool executeFile(const std::string& path);
    bool initialize(const std::string& databasePath, const std::string& schemaPath);

private:
    void setErrorFromSqlite(int resultCode);

    sqlite3* db{nullptr};
    std::string lastErrorMessage;
};
