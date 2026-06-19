
#include"accountService.h"
#include "database/repository/userRepository.h"
#include <optional>

bool AccountService::isLoggedIn() {
    return !currentUser.isGuest();
}

bool AccountService::login(const std::string &name, const std::string &password) {
    if (currentUser.getId() != 0) {return false;}
    auto user = userRepo->findByName(name);
    if (!user.has_value()) {return false;}
    if (user->checkPassword(password)) {
        currentUser = user.value();
        return true;
    }
    return false;
}

bool AccountService::logout(){
    currentUser.init();
    return true;
}

bool AccountService::signup(const std::string &name, const std::string &password){
    if(userRepo == nullptr) {return false;}
    if(userRepo->findByName(name) != std::nullopt){return false;}
    User newUser(name, password);
    return userRepo->insert(newUser);
}


UserInfo AccountService::getInfo() {
    updateInfo();
    return userInfo;
}


void AccountService::updateInfo() {
    if (userRepo != nullptr && currentUser.getId() > 0) {
        const auto user = userRepo->findById(currentUser.getId());
        if (user.has_value()) {
            currentUser = user.value();
        }
    }
    userInfo = currentUser;
}
