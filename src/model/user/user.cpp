#include "user.h"

#include <utility>

User::User(int id, std::string name, std::string password, int point)
    : UserBase(id, std::move(name), std::move(password)), point(point) {}

User::User(std::string name, std::string password, int point)
    : UserBase(std::move(name), std::move(password)), point(point) {}

void User::addPoint(int point) {
    this->point += point;
}

bool User::usePoint(int point) {
    if (point < 0 || this->point < point) {
        return false;
    }
    this->point -= point;
    return true;
}

bool User::subPoint(int point) {
    if (point < 0) {
        return false;
    }
    this->point -= point;
    return true;
}
