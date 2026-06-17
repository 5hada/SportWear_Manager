
#include <string>

class AuthController {

public:
    AuthController();

    bool logout();
    bool login(std::string name, std::string password);

    std::string getName();
    int getPoint();
};