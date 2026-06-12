#include "sqlite3.h"
#include <string>

class DataBaseManager {
    sqlite3 *db_ = nullptr;

public:
    DataBaseManager() = default;
    explicit DataBaseManager(const std::string &path);

    ~DataBaseManager();

    DataBaseManager(const DataBaseManager &) = delete;
    DataBaseManager &operator=(const DataBaseManager &) = delete;

    bool open(const std::string &path);
    void close();
    bool isOpen() const;
    sqlite3 *handle() const;
    bool execute(const std::string &sql, std::string *errorMessage = nullptr);
};
