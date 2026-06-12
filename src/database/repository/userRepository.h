#include "model/user/user.h"
#include <optional>
#include <vector>

class UserRepository {
    std::vector<User> users_;

public:
    UserRepository();

    const std::vector<User> &findAll() const;
    std::optional<User> findById(int id) const;
    std::optional<User> findByName(const std::string &name) const;
    void save(const User &user);
};
