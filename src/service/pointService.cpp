#include "pointService.h"

PointService::PointService(UserRepository *users) : users_(users) {}

bool PointService::addPoint(int userId, int point)
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

bool PointService::usePoint(int userId, int point)
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
