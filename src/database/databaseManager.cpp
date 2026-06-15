#include "databaseManager.h"

#include <fstream>
#include <sstream>
#include <utility>

DataBaseManager::DataBaseManager(std::string path)
{
    open(path);
}

DataBaseManager::~DataBaseManager() {
    close();
}

DataBaseManager::DataBaseManager(DataBaseManager&& other) noexcept
    : db(std::exchange(other.db, nullptr)),
      lastErrorMessage(std::move(other.lastErrorMessage))
{
}

DataBaseManager& DataBaseManager::operator=(DataBaseManager&& other) noexcept
{
    if (this != &other) {
        close();
        db = std::exchange(other.db, nullptr);
        lastErrorMessage = std::move(other.lastErrorMessage);
    }
    return *this;
}

bool DataBaseManager::open(const std::string& path)
{
    close();

    const int result = sqlite3_open(path.c_str(), &db);
    if (result != SQLITE_OK) {
        setErrorFromSqlite(result);
        close();
        return false;
    }

    return execute("PRAGMA foreign_keys = ON;");
}

void DataBaseManager::close()
{
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DataBaseManager::isOpen() const
{
    return db != nullptr;
}

sqlite3* DataBaseManager::handle() const
{
    return db;
}

const std::string& DataBaseManager::lastError() const
{
    return lastErrorMessage;
}

bool DataBaseManager::execute(const std::string& sql)
{
    if (db == nullptr) {
        lastErrorMessage = "database is not open";
        return false;
    }

    char* rawError = nullptr;
    const int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &rawError);
    if (result != SQLITE_OK) {
        lastErrorMessage = rawError != nullptr ? rawError : sqlite3_errmsg(db);
        sqlite3_free(rawError);
        return false;
    }

    lastErrorMessage.clear();
    return true;
}

bool DataBaseManager::executeFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        lastErrorMessage = "failed to open SQL file: " + path;
        return false;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return execute(buffer.str());
}

bool DataBaseManager::initialize(const std::string& databasePath, const std::string& schemaPath)
{
    return open(databasePath) && executeFile(schemaPath);
}

void DataBaseManager::setErrorFromSqlite(int resultCode)
{
    if (db != nullptr) {
        lastErrorMessage = sqlite3_errmsg(db);
        return;
    }
    lastErrorMessage = sqlite3_errstr(resultCode);
}
