
#include "model/product/pointAction.h"

class UserRepository;

class PointService{
    UserRepository* userRepo{nullptr};

    static int calPoint(int price);
public:
    PointService(UserRepository* userRepo): userRepo(userRepo) {}

    int getPoint(int userId);

    bool handlePoint(PointAction action, int userId, int point);

    bool reward(int userId, int totalPrice);
    bool revert(int userId, int usedPoint, int totalPrice);
};