#include "userBase.h"

class Guest : public UserBase {
public:
    Guest(): UserBase(0, "guest", "") {}
};
