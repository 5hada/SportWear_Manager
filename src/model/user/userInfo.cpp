#include "userInfo.h"


UserInfo* UserInfo::operator=(User& user) {
    setRole(user.getRole());
    setName(user.getName());
    setPoint(user.getPoint());
    return this;
}