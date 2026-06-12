#include "review.h"

#include <utility>

Review::Review(int id, int userId, int productId, int rating, std::string comment)
    : id_(id), userId_(userId), productId_(productId), rating_(rating), comment_(std::move(comment)) {}

int Review::id() const {
    return id_;
}

int Review::userId() const {
    return userId_;
}

int Review::productId() const {
    return productId_;
}

int Review::rating() const {
    return rating_;
}

const std::string &Review::comment() const {
    return comment_;
}
