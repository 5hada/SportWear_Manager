#include "database/repository/userRepository.h"

#include <optional>

class LoginService {
    UserRepository *users_ = nullptr;
    
public:
    explicit LoginService(UserRepository *users);

    std::optional<User> login(const std::string &name, const std::string &password) const;
};
