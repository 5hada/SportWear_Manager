#include "database/repository/userRepository.h"

class PointService {
    UserRepository *users_ = nullptr;
    
public:
    explicit PointService(UserRepository *users);

    bool addPoint(int userId, int point);
    bool usePoint(int userId, int point);
};
