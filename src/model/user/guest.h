#include "userBase.h"

class Guest : public UserBase {
public:
    Guest() = default;
    explicit Guest(int id);
};
