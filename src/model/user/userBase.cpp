#include "userBase.h"

#include <utility>

UserBase::UserBase(int id, std::string name, std::string password)
    : id_(id), name_(std::move(name)), password_(std::move(password))
{
}

int UserBase::id() const
{
    return id_;
}

const std::string &UserBase::name() const
{
    return name_;
}

const std::string &UserBase::password() const
{
    return password_;
}

void UserBase::setId(int id)
{
    id_ = id;
}

void UserBase::setName(std::string name)
{
    name_ = std::move(name);
}

void UserBase::setPassword(std::string password)
{
    password_ = std::move(password);
}

bool UserBase::checkPassword(const std::string &password) const
{
    return password_ == password;
}
