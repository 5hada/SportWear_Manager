#pragma once

#include "userBase.h"

enum class UserRole {
    Guest,
    User,
    Admin
};
class User : public UserBase {
    UserRole role;
    long long point = 0;

public:
    User();
    User(int id, std::string name, std::string password, long long point = 0);
    User(std::string name, std::string password, long long point = 0);
    
    bool isGuest();
    void init();

    UserRole getRole() const {return role;}
    void setRole(UserRole role) {this->role = role;}

    long long getPoint() const {return point;}
    bool setPoint(long long point);

    bool addPoint(long long point);
    bool usePoint(long long point);
    bool subPoint(long long point);
};
