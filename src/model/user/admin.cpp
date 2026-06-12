#include "admin.h"

#include <utility>

Admin::Admin(std::string name, std::string password)
    : UserBase(1, std::move(name), std::move(password)) {}
