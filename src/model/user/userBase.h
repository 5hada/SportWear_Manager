#pragma once

#include <string>

class UserBase{
    int id=0;
    std::string name;
    std::string password;

public:
    UserBase() {}
    UserBase(int id, std::string name, std::string password);
    UserBase(std::string name, std::string password);

    

    int getId() const { return id; }
    const std::string &getName() const { return name; }

    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
    void setPassword(std::string password) { this->password = password; }

    bool checkPassword(const std::string &password) const;
};
