#pragma once

#include "database/databaseManager.h"
#include "model/user/user.h"
#include <optional>
#include <vector>

class UserRepository
{
public:
    explicit UserRepository(DataBaseManager* database = nullptr);

    void setDatabase(DataBaseManager* database);

    const std::vector<User>& findAll() const;
    std::optional<User> findById(int id) const;
    std::optional<User> findByName(const std::string& name) const;
    void save(const User& user);

private:
    bool hasDatabase() const;
    static User userFromStatement(sqlite3_stmt* statement);

    DataBaseManager* database{nullptr};
    mutable std::vector<User> users;
};
