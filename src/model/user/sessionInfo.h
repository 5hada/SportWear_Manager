
#include<QString>

enum class UserRole {
    Guest,
    Member,
    Admin
};

struct SessionInfo {
    QString name;
    UserRole role;
    bool isLoggedIn;
};