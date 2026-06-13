#include "userBase.h"

#include <utility>

UserBase::UserBase(int id, std::string name, std::string password)
    : id(id), name(std::move(name)), password(std::move(password)) {}

UserBase::UserBase(std::string name, std::string password)
    : name(std::move(name)), password(std::move(password)) {}

bool UserBase::checkPassword(const std::string &password) const {
    return this->password == password;
}
