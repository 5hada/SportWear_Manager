#pragma once

#include "user.h"
#include <string>

using std::string;


class UserInfo {
    UserRole role;
    string name;
    int point;

    std::string infoText;

public:
    UserInfo() {};

    void setRole(UserRole role) {this->role = role;}
    void setName(string name) {this->name = name;}
    void setPoint(int point) {this->point = point;}
    void setInfoText(string infoTet) {this->infoText = infoTet;}

    UserRole getRole() {return role;}
    string getName() {return name;}
    int getPoint() {return point;}
    string getInfoText() {return infoText;}

    UserInfo* operator=(User& user);
};
