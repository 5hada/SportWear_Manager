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

public:
    User(int id, std::string name, std::string password, int point = 0);
    User(std::string name, std::string password, int point = 0);

    int getPoint() const {return point;}
    void setPoint(int point) {this->point = point;}

    void addPoint(int point);
    bool usePoint(int point);
    bool subPoint(int point);
};
