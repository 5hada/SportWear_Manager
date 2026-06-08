#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "model/user/user.h"

#include <optional>
#include <vector>

class UserRepository {
public:
    UserRepository();

    const std::vector<User> &findAll() const;
    std::optional<User> findById(int id) const;
    std::optional<User> findByName(const std::string &name) const;
    void save(const User &user);

private:
    std::vector<User> users_;
};

#endif // USERREPOSITORY_H
