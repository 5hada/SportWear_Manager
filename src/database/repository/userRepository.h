#pragma once

#include "repositoryBase.h"
#include "model/user/user.h"
#include <optional>
#include <vector>

class UserRepository: public RepositoryBase{
    static User userFromStatement(sqlite3_stmt* statement);
public:
    UserRepository(DatabaseManager* db): RepositoryBase(db) {}


    const std::vector<User> findAll() const;
    std::optional<User> findById(int id) const;
    std::optional<User> findByName(const std::string& name) const;
    
    bool insert(const User& user);
    bool updatePoint(const User& user);
};
