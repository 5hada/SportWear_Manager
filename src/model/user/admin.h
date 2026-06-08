#ifndef ADMIN_H
#define ADMIN_H

#include "userBase.h"

class Admin : public UserBase {
public:
    Admin() = default;
    Admin(int id, std::string name, std::string password);
};

#endif // ADMIN_H
