#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review {
public:
    Review() = default;
    Review(int id, int userId, int productId, int rating, std::string comment)
        : id_(id), userId_(userId), productId_(productId), rating_(rating), comment_(std::move(comment))
    {
    }

    int id() const { return id_; }
    int userId() const { return userId_; }
    int productId() const { return productId_; }
    int rating() const { return rating_; }
    const std::string &comment() const { return comment_; }

private:
    int id_ = 0;
    int userId_ = 0;
    int productId_ = 0;
    int rating_ = 0;
    std::string comment_;
};

#endif // REVIEW_H
