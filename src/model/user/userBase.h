#include <string>

class UserBase {
    int id_ = 0;
    std::string name_;
    std::string password_;

public:
    UserBase() = default;
    UserBase(int id, std::string name, std::string password);

    virtual ~UserBase() = default;

    int id() const;
    const std::string &name() const;
    const std::string &password() const;

    void setId(int id);
    void setName(std::string name);
    void setPassword(std::string password);

    bool checkPassword(const std::string &password) const;
};
