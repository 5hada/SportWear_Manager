#include"signupService.h"


void SignupService::signup(const std::string &name, const std::string &password){
    if(userRepo == nullptr) {return;}
    if(userRepo->findByName(name) != std::nullopt){return;}

}