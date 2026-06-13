#pragma once

#include "userBase.h"

class User : public UserBase {
    int point = 0;

public:
    User(int id, std::string name, std::string password, int point = 0);
    User(std::string name, std::string password, int point = 0);

    int getPoint() const;
    void setPoint();

    void addPoint(int point);
    bool usePoint(int point);
};
