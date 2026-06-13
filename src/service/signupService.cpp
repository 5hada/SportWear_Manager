#include"signupService.h"


bool SignupService::signup(const std::string &name, const std::string &password){
    if(userRepo == nullptr) {return false;}
    if(userRepo->findByName(name) != std::nullopt){return false;}

    User newUser(name, password);
    return userRepo->save(newUser);
}