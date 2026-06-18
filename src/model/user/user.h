#pragma once

#include "userBase.h"

enum class UserRole {
    Guest,
    User,
    Admin
};
class User : public UserBase {
    UserRole role;
    int point = 0;

    void findRole(int id = 0);
public:
    User();
    User(int id, std::string name, std::string password, int point = 0);
    User(std::string name, std::string password, int point = 0);
    
    bool isGuest();
    void init();

    UserRole getRole() const {return role;}
    void setRole(UserRole role) {this->role = role;}

    int getPoint() const {return point;}
    bool setPoint(int point);

    bool addPoint(int point);
    bool usePoint(int point);
    bool subPoint(int point);
};
