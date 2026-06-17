
#include "model/product/pointAction.h"

class UserRepository;

class PointService{
    UserRepository* userRepo{nullptr};

    static long long calPoint(long long price);
public:
    PointService(UserRepository* userRepo): userRepo(userRepo) {}

    long long getPoint(int userId);

    bool handlePoint(PointAction action, int userId, long long point);

    bool reward(int userId, long long totalPrice);
    bool revert(int userId, long long usedPoint, long long totalPrice);
};
