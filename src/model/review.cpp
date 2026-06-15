#include "review.h"

#include <utility>

Review::Review(int id, int userId, int productId, int rating, std::string comment)
    : id(id), userId(userId), productId(productId), rating(rating), comment(std::move(comment)) {}

Review::Review(int userId, int productId, int rating, std::string comment)
    : userId(userId), productId(productId), rating(rating), comment(std::move(comment)) {}


