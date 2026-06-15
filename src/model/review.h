#pragma once

#include <string>

class Review {
    int id_ = 0;
    int userId_ = 0;
    int productId_ = 0;
    int rating_ = 0;
    std::string comment_;

    int id_ = 0;
    int userId_ = 0;
    int productId_ = 0;
    int rating_ = 0;
    std::string comment_;

public:
    Review() = default;
    Review(int id, int userId, int productId, int rating, std::string comment);

    int id() const;
    int userId() const;
    int productId() const;
    int rating() const;
    const std::string &comment() const;
};
