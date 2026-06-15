#pragma once

#include "database/databaseManager.h"
#include "model/user/user.h"
#include <optional>
#include <vector>

class UserRepository{
    DataBaseManager* database{nullptr};
    mutable std::vector<User> users;


    bool hasDatabase() const;
    static User userFromStatement(sqlite3_stmt* statement);

public:
    explicit UserRepository(DataBaseManager* database = nullptr);

    void setDatabase(DataBaseManager* database);

    const std::vector<User>& findAll() const;
    std::optional<User> findById(int id) const;
    std::optional<User> findByName(const std::string& name) const;
    
    bool save(const User& user);

};
