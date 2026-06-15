
#include"accountService.h"
#include "model/user/userBase.h"
#include <optional>


bool AccountService::login(const std::string &name, const std::string &password) {
    if (currentUser->getId() != 0) {return false;}
    auto user = userRepo->findByName(name);
    if (!user.has_value()) {return false;}
    if (user->checkPassword(password)) {
        *currentUser = user.value();
        return true;
    }
    return false;
}

bool AccountService::logout(){
    currentUser = guest;
    return true;
}

bool AccountService::signup(const std::string &name, const std::string &password){
    if(userRepo == nullptr) {return false;}
    if(userRepo->findByName(name) != std::nullopt){return false;}
    User newUser(name, password);
    return userRepo->insert(newUser);
}

int AccountService::getUserPoint(){
    if(currentUser->getId() <= 1) {return 0;}
    auto* user = dynamic_cast<User*>(currentUser);
    return user->getPoint();
}