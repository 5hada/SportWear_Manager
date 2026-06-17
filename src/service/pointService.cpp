#include "pointService.h"
#include "database/repository/userRepository.h"
#include <optional>



int PointService::getPoint(int userId){
    return userRepo->findById(userId)->getPoint();
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
    if(userId <= 1) {return false;}
    std::optional<User> user = userRepo->findById(userId);
    user->addPoint(calPoint(totalPrice));
    return userRepo->updatePoint(user.value());
}

bool PointService::revert(int userId, int usedPoint, int totalPrice){
    if(userId <= 1) {return false;}
    std::optional<User> user = userRepo->findById(userId);
    int value = usedPoint - calPoint(totalPrice);
    if (value > 0){
        user->addPoint(value);
    }
    else if (value < 0){
        user->subPoint(-value);
    }
    return userRepo->updatePoint(user.value());
}

int PointService::calPoint(int price){
    float rate = 5;
    return price*(rate/100);
}