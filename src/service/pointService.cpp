#include "pointService.h"
#include "database/repository/userRepository.h"
#include <optional>



long long PointService::getPoint(int userId){
    return userRepo->findById(userId)->getPoint();
}

bool PointService::handlePoint(PointAction action, int userId, long long point){
    std::optional<User> user = userRepo->findById(userId);
    if (user == std::nullopt) {return false;}
    switch (action){
        case PointAction::Add:
            user->addPoint(point);
            break;
        case PointAction::Sub:
            user->usePoint(point);
            break;
        case PointAction::Set:
            user->setPoint(point);
            break;
        case PointAction::Init:
            user->setPoint(0);
            break;
    }
    return userRepo->updatePoint(user.value());
}

bool PointService::reward(int userId, long long totalPrice){
    if(userId <= 1) {return false;}
    std::optional<User> user = userRepo->findById(userId);
    user->addPoint(calPoint(totalPrice));
    return userRepo->updatePoint(user.value());
}

bool PointService::revert(int userId, long long usedPoint, long long totalPrice){
    if(userId <= 1) {return false;}
    std::optional<User> user = userRepo->findById(userId);
    long long value = usedPoint - calPoint(totalPrice);
    if (value > 0){
        user->addPoint(value);
    }
    else if (value < 0){
        user->subPoint(-value);
    }
    return userRepo->updatePoint(user.value());
}

long long PointService::calPoint(long long price){
    return price * 5 / 100;
}
