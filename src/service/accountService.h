
#include "model/user/user.h"
#include "model/ui/userInfo.h"

class UserRepository;

class AccountService {
    UserRepository* userRepo{nullptr};

    User currentUser;
    UserInfo userInfo;

    void getUser();
    void updateInfo();
public:
    AccountService(UserRepository* userRepo): userRepo(userRepo) {}

    int getUserId() const {return currentUser.getId();}
    const string getUserName() const {return currentUser.getName();}

    void setUserRepo(UserRepository* userRepo) {this->userRepo = userRepo;}

    bool login(const string& name, const string& password);
    bool logout();
    bool signup(const string& name, const string& password);

    bool isLoggedIn();


    UserInfo getInfo();
};