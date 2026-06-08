#include "admin.h"

#include <utility>

Admin::Admin(int id, std::string name, std::string password)
    : UserBase(id, std::move(name), std::move(password))
{
}
