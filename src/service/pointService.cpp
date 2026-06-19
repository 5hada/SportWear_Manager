#include "pointService.h"
#include "database/repository/userRepository.h"
#include <optional>



int PointService::getPoint(int userId){
    const auto user = userRepo->findById(userId);
    return user.has_value() ? user->getPoint() : 0;
}

bool PointService::handlePoint(PointAction action, int userId, int point){
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

bool PointService::reward(int userId, int totalPrice){
    if(userId <= 1) {return true;}
    std::optional<User> user = userRepo->findById(userId);
    if (user == std::nullopt) {return false;}
    const int point = calPoint(totalPrice);
    if (point == 0) {return true;}
    if (!user->addPoint(point)) {return false;}
    return userRepo->updatePoint(user.value());
}

bool PointService::revert(int userId, int usedPoint, int totalPrice){
    if(userId <= 1) {return true;}
    std::optional<User> user = userRepo->findById(userId);
    if (user == std::nullopt) {return false;}
    int value = usedPoint - calPoint(totalPrice);
    if (value == 0) {return true;}
    if (value > 0){
        if (!user->addPoint(value)) {return false;}
    }
    else if (value < 0){
        if (!user->subPoint(-value)) {return false;}
    }
    return userRepo->updatePoint(user.value());
}

int PointService::calPoint(int price){
    float rate = 5;
    return price*(rate/100);
}
