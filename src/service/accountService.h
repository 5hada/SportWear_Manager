#include "database/repository/userRepository.h"

class AccountService{
    UserRepository* userRepo{nullptr};

public:
    AccountService(UserRepository* userRepo):userRepo(userRepo){}
    void setUserRepo(UserRepository* userRepo){this->userRepo = userRepo;}

    std::optional<User> login(const std::string &name, const std::string &password) const;
    bool signup(const std::string &name, const std::string &password);
};