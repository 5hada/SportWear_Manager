#include "loginService.h"

LoginService::LoginService(UserRepository *users) : users_(users) {}

std::optional<User> LoginService::login(const std::string &name, const std::string &password) const {
    if (users_ == nullptr) {
        return std::nullopt;
    }

    auto user = users_->findByName(name);
    if (user.has_value() && user->checkPassword(password)) {
        return user;
    }
    return std::nullopt;
}
