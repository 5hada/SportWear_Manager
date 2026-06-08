#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include "database/repository/userRepository.h"

#include <optional>

class LoginService {
public:
    explicit LoginService(UserRepository *users) : users_(users) {}

    std::optional<User> login(const std::string &name, const std::string &password) const
    {
        if (users_ == nullptr) {
            return std::nullopt;
        }

        auto user = users_->findByName(name);
        if (user.has_value() && user->checkPassword(password)) {
            return user;
        }
        return std::nullopt;
    }

private:
    UserRepository *users_ = nullptr;
};

#endif // LOGINSERVICE_H
