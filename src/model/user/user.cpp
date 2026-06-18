#include "user.h"
#include "userBase.h"

#include <utility>

User::User(): UserBase() {
    init();
}

User::User(int id, std::string name, std::string password, int point)
    : UserBase(id, std::move(name), std::move(password)), point(point) {
        findRole(id);
    }

User::User(std::string name, std::string password, int point)
    : UserBase(std::move(name), std::move(password)), point(point) {
        findRole();
    }


void User::findRole(int id) {
    if (id == 0) {
        setRole(UserRole::Guest);
        return;
    }
    if (id == 1) {
        setRole(UserRole::Admin);
        return;
    }
    setRole(UserRole::User);
}

void User::init() {
    setId(0);
    setName("Guest");
    setPassword("");
    setRole(UserRole::Guest);
}

bool User::isGuest() {
    return role == UserRole::Guest;
}


bool User::setPoint(int point) {
    if (isGuest()) {
        this->point = 0;
        return false;
    }
    this->point = point;
    return true;
}


bool User::addPoint(int point) {
    if (isGuest()) {return false;}
    this->point += point;
    return true;
}

bool User::usePoint(int point) {
    if (isGuest() || point < 0 || this->point < point) {
        return false;
    }
    this->point -= point;
    return true;
}

bool User::subPoint(int point) {
    if (isGuest() || point < 0) {
        return false;
    }
    this->point -= point;
    return true;
}
