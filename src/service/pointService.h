#ifndef POINTSERVICE_H
#define POINTSERVICE_H

#include "database/repository/userRepository.h"

class PointService {
public:
    explicit PointService(UserRepository *users);

    bool addPoint(int userId, int point);
    bool usePoint(int userId, int point);

private:
    UserRepository *users_ = nullptr;
};

#endif // POINTSERVICE_H
