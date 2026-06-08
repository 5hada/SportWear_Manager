#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "model/user/user.h"

#include <optional>
#include <vector>

class UserRepository {
public:
    UserRepository() { save(User(1, "user", "1234", 1000)); }

    const std::vector<User> &findAll() const { return users_; }

    std::optional<User> findById(int id) const
    {
        for (const auto &user : users_) {
            if (user.id() == id) {
                return user;
            }
        }
        return std::nullopt;
    }

    std::optional<User> findByName(const std::string &name) const
    {
        for (const auto &user : users_) {
            if (user.name() == name) {
                return user;
            }
        }
        return std::nullopt;
    }

    void save(const User &user)
    {
        for (auto &stored : users_) {
            if (stored.id() == user.id()) {
                stored = user;
                return;
            }
        }
        users_.push_back(user);
    }

private:
    std::vector<User> users_;
};

#endif // USERREPOSITORY_H
