#pragma once

#include <string>

using std::string;


enum class UiUserRole {
    Guest,
    User,
    Admin
};

class UserInfo {
    UiUserRole role{UiUserRole::Guest};
    string name;
    int point{0};

    std::string infoText;

public:
    UserInfo() {};

    void setRole(UiUserRole role) {this->role = role;}
    void setName(string name) {this->name = name;}
    void setPoint(int point) {this->point = point;}
    void setInfoText(string infoTet) {this->infoText = infoTet;}

    UiUserRole getRole() const {return role;}
    string getName() const {return name;}
    int getPoint() const {return point;}
    string getInfoText() const {return infoText;}

};
