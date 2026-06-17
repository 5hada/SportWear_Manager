
#include "model/user/user.h"

class UserRepository;

class AccountService {
    UserRepository* userRepo{nullptr};

    User currentUser;

    void getUser();
public:
    AccountService(UserRepository* userRepo): userRepo(userRepo) {}

    int getUserId() const {return currentUser.getId();}
    const std::string getUserName() const {return currentUser.getName();}

    void setUserRepo(UserRepository* userRepo) {this->userRepo = userRepo;}

    bool login(const std::string& name, const std::string& password);
    bool logout();
    bool signup(const std::string& name, const std::string& password);

    bool isLoggedIn();
};