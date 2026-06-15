#include "database/repository/userRepository.h"
#include "model/user/guest.h"
#include "model/user/userBase.h"

class AccountService{
    UserRepository* userRepo{nullptr};

    UserBase* currentUser{nullptr};
    Guest* guest;

    User* castUser();
public:
    AccountService(UserRepository* userRepo): userRepo(userRepo) {}

    int getUserId() const {return currentUser->getId();}
    const std::string getUserName() const {return currentUser->getName();}
    int getUserPoint();

    void setUserRepo(UserRepository* userRepo) {this->userRepo = userRepo;}

    bool login(const std::string& name, const std::string& password);
    bool logout();
    bool signup(const std::string& name, const std::string& password);
};