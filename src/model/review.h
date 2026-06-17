#pragma once

#include <string>

class Review {
    int id = 0;
    int productId = 0;
    int userId = 0;
    int rating = 0;
    std::string comment;

public:
    Review() = default;
    Review(int id, int userId, int productId, int rating, std::string comment);
    Review(int userId, int productId, int rating, std::string comment);

    int getId() const {return id;}
    int getUserId() const { return userId; }
    int getProductId() const{ return productId;}
    int getRating() const {return rating;}
    const std::string &getComment() const{return comment;}
};
