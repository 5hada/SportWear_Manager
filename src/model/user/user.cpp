#include "user.h"

#include <utility>

User::User(int id, std::string name, std::string password, int point)
    : UserBase(id, std::move(name), std::move(password)), point(point) {}

int User::getPoint() const {
    return point;
}

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
