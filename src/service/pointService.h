#ifndef POINTSERVICE_H
#define POINTSERVICE_H

#include "database/repository/userRepository.h"

class PointService {
public:
    explicit PointService(UserRepository *users) : users_(users) {}

    bool addPoint(int userId, int point)
    {
        if (users_ == nullptr || point < 0) {
            return false;
        }
        auto user = users_->findById(userId);
        if (!user.has_value()) {
            return false;
        }
        user->addPoint(point);
        users_->save(*user);
        return true;
    }

    bool usePoint(int userId, int point)
    {
        if (users_ == nullptr) {
            return false;
        }
        auto user = users_->findById(userId);
        if (!user.has_value() || !user->usePoint(point)) {
            return false;
        }
        users_->save(*user);
        return true;
    }

private:
    UserRepository *users_ = nullptr;
};

#endif // POINTSERVICE_H
