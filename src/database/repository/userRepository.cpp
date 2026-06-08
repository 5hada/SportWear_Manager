#include "userRepository.h"

UserRepository::UserRepository()
{
    save(User(1, "user", "1234", 1000));
}

const std::vector<User> &UserRepository::findAll() const
{
    return users_;
}

std::optional<User> UserRepository::findById(int id) const
{
    for (const auto &user : users_) {
        if (user.id() == id) {
            return user;
        }
    }
    return std::nullopt;
}

std::optional<User> UserRepository::findByName(const std::string &name) const
{
    for (const auto &user : users_) {
        if (user.name() == name) {
            return user;
        }
    }
    return std::nullopt;
}

void UserRepository::save(const User &user)
{
    for (auto &stored : users_) {
        if (stored.id() == user.id()) {
            stored = user;
            return;
        }
    }
    users_.push_back(user);
}
