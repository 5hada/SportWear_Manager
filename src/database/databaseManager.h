#pragma once

#include "sqlite3.h"

#include <string>

class DataBaseManager
{
public:
    DataBaseManager() = default;
    explicit DataBaseManager(std::string path);
    ~DataBaseManager();

    DataBaseManager(const DataBaseManager&) = delete;
    DataBaseManager& operator=(const DataBaseManager&) = delete;

    DataBaseManager(DataBaseManager&& other) noexcept;
    DataBaseManager& operator=(DataBaseManager&& other) noexcept;

    bool open(const std::string& path);
    void close();
    bool isOpen() const;

    sqlite3* handle() const;
    const std::string& lastError() const;

    bool execute(const std::string& sql);
    bool executeFile(const std::string& path);
    bool initialize(const std::string& databasePath, const std::string& schemaPath);

private:
    void setErrorFromSqlite(int resultCode);

    sqlite3* db{nullptr};
    std::string lastErrorMessage;
};
