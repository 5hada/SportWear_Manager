#include "databaseManager.h"

#include <fstream>
#include <sstream>
#include <utility>

DatabaseManager::DatabaseManager(DatabaseManager&& other) noexcept
    : db(std::exchange(other.db, nullptr)),
      lastErrorMessage(std::move(other.lastErrorMessage))
{}

DatabaseManager& DatabaseManager::operator=(DatabaseManager&& other) noexcept {
    if (this != &other) {
        close();
        db = std::exchange(other.db, nullptr);
        lastErrorMessage = std::move(other.lastErrorMessage);
    }
    return *this;
}

bool DatabaseManager::open(const std::string& path) {
    close();

    const int result = sqlite3_open(path.c_str(), &db);
    if (result != SQLITE_OK) {
        setErrorFromSqlite(result);
        close();
        return false;
    }

    return execute("PRAGMA foreign_keys = ON;");
}

void DatabaseManager::close() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::execute(const std::string& sql) {
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

bool DatabaseManager::executeFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        lastErrorMessage = "failed to open SQL file: " + path;
        return false;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return execute(buffer.str());
}

bool DatabaseManager::initialize(const std::string& databasePath, const std::string& schemaPath) {
    if (!open(databasePath)) {
        return false;
    }
    if (!executeFile(schemaPath)) {
        close();
        return false;
    }
    return true;
}

void DatabaseManager::setErrorFromSqlite(int resultCode) {
    if (db != nullptr) {
        lastErrorMessage = sqlite3_errmsg(db);
        return;
    }
    lastErrorMessage = sqlite3_errstr(resultCode);
}
