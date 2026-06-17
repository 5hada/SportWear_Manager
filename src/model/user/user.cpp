#include "user.h"
#include "userBase.h"

#include <utility>

User::User(): UserBase() {
    init();
}

User::User(int id, std::string name, std::string password, long long point)
    : UserBase(id, std::move(name), std::move(password)), point(point) {}

User::User(std::string name, std::string password, long long point)
    : UserBase(std::move(name), std::move(password)), point(point) {}


void User::init() {
    setId(0);
    setName("Guest");
    setPassword("");
}

bool User::isGuest() {
    return role == UserRole::Guest;
}


bool User::setPoint(long long point) {
    if (isGuest()) {
        this->point = 0;
        return false;
    }
    this->point = point;
    return true;
}


bool User::addPoint(long long point) {
    if (isGuest()) {return false;}
    this->point += point;
    return true;
}

bool User::usePoint(long long point) {
    if (isGuest() || point < 0 || this->point < point) {
        return false;
    }
    this->point -= point;
    return true;
}

bool User::subPoint(long long point) {
    if (isGuest() || point < 0) {
        return false;
    }
    this->point -= point;
    return true;
}
