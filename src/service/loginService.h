#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include "database/repository/userRepository.h"

#include <optional>

class LoginService {
public:
    explicit LoginService(UserRepository *users);

    std::optional<User> login(const std::string &name, const std::string &password) const;

private:
    UserRepository *users_ = nullptr;
};

#endif // LOGINSERVICE_H
