#pragma once

#include "repositoryBase.h"

#include "model/user/user.h"

#include <optional>
#include <vector>

using std::optional;
using std::vector;
using std::string;

class UserRepository: public RepositoryBase{
    static User userFromStatement(sqlite3_stmt* statement);
public:
    UserRepository(DatabaseManager* db): RepositoryBase(db) {}


    const vector<User> findAll() const;
    optional<User> findById(int id) const;
    optional<User> findByName(const string& name) const;
    
    bool insert(const User& user);
    bool updatePoint(const User& user);
};
