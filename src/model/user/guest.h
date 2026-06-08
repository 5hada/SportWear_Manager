#ifndef GUEST_H
#define GUEST_H

#include "userBase.h"

class Guest : public UserBase {
public:
    Guest() = default;
    explicit Guest(int id = 0) : UserBase(id, "guest", "") {}
};

#endif // GUEST_H
