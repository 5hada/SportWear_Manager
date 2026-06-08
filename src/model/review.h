#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review {
public:
    Review() = default;
    Review(int id, int userId, int productId, int rating, std::string comment);

    int id() const;
    int userId() const;
    int productId() const;
    int rating() const;
    const std::string &comment() const;

private:
    int id_ = 0;
    int userId_ = 0;
    int productId_ = 0;
    int rating_ = 0;
    std::string comment_;
};

#endif // REVIEW_H
