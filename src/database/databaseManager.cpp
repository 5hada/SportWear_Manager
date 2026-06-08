#include "databaseManager.h"

DataBaseManager::DataBaseManager(const std::string &path)
{
    open(path);
}

DataBaseManager::~DataBaseManager()
{
    close();
}

bool DataBaseManager::open(const std::string &path)
{
    close();
    return sqlite3_open(path.c_str(), &db_) == SQLITE_OK;
}

void DataBaseManager::close()
{
    if (db_ != nullptr) {
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

bool DataBaseManager::isOpen() const
{
    return db_ != nullptr;
}

sqlite3 *DataBaseManager::handle() const
{
    return db_;
}

bool DataBaseManager::execute(const std::string &sql, std::string *errorMessage)
{
    if (db_ == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = "database is not open";
        }
        return false;
    }

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
