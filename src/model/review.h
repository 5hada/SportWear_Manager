#pragma once

#include <string>
#include <vector>

class Review;

using std::string;
using Reviews = std::vector<Review>;

class Review {
    int id = 0;
    int productId = 0;
    int userId = 0;
    int rating = 0;
    string comment;

public:
    Review() = default;
    Review(int id, int userId, int productId, int rating, string comment);
    Review(int userId, int productId, int rating, string comment);

    int getId() const {return id;}
    int getUserId() const { return userId; }
    int getProductId() const{ return productId;}
    int getRating() const {return rating;}
    const string &getComment() const{return comment;}
};
