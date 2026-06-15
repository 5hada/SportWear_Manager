
#include"accountService.h"



std::optional<User> AccountService::login(const std::string &name, const std::string &password) const {
    if (userRepo == nullptr) {
        return std::nullopt;
    }

    auto user = userRepo->findByName(name);
    if (user.has_value() && user->checkPassword(password)) {
        return user;
    }
    return std::nullopt;
}

bool AccountService::signup(const std::string &name, const std::string &password){
    if(userRepo == nullptr) {return false;}
    if(userRepo->findByName(name) != std::nullopt){return false;}

    User newUser(name, password);
    return userRepo->save(newUser);
}