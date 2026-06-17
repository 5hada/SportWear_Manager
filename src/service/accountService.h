
#include "model/user/guest.h"
#include "model/user/userBase.h"

class UserRepository;

class AccountService {
    UserRepository* userRepo{nullptr};

    bool isLoggedIn = false;
    UserBase currentUser;
    Guest guest;

public:
    AccountService(UserRepository* userRepo): userRepo(userRepo) {currentUser = guest;}

    int getUserId() const {return currentUser.getId();}
    const std::string getUserName() const {return currentUser.getName();}

    void setUserRepo(UserRepository* userRepo) {this->userRepo = userRepo;}

    bool login(const std::string& name, const std::string& password);
    bool logout();
    bool signup(const std::string& name, const std::string& password);

    bool loggedIn() {return isLoggedIn;}
};