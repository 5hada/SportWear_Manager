#include "database/repository/userRepository.h"


class SignupService{
    UserRepository *userRepo = nullptr;

public:
    explicit SignupService(UserRepository *users) : userRepo(users) {}


    bool signup(const std::string &name, const std::string &password);
};