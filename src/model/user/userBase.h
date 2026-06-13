#pragma once

#include <string>

class UserBase{
    int id;
    std::string name;
    std::string password;

public:
    UserBase(int id, std::string name, std::string password);
    UserBase(std::string name, std::string password);

    virtual ~UserBase() = default;

    int getId() const { return id; }
    const std::string &getName() const { return name; }
    const std::string &getPassword() const { return password; }

    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
    void setPassword(std::string password) { this->password = password; }

    bool checkPassword(const std::string &password) const;
};
