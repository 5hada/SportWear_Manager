#ifndef USERBASE_H
#define USERBASE_H

#include <string>

class UserBase {
public:
    UserBase() = default;
    UserBase(int id, std::string name, std::string password)
        : id_(id), name_(std::move(name)), password_(std::move(password))
    {
    }

    virtual ~UserBase() = default;

    int id() const { return id_; }
    const std::string &name() const { return name_; }
    const std::string &password() const { return password_; }

    void setId(int id) { id_ = id; }
    void setName(std::string name) { name_ = std::move(name); }
    void setPassword(std::string password) { password_ = std::move(password); }

    bool checkPassword(const std::string &password) const { return password_ == password; }

private:
    int id_ = 0;
    std::string name_;
    std::string password_;
};

#endif // USERBASE_H
