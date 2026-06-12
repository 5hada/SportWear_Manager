#include "reviewService.h"

ReviewService::ReviewService(ReviewRepository *reviews) : reviews_(reviews) {}

bool ReviewService::addReview(int userId, int productId, int rating, const std::string &comment) {
    if (reviews_ == nullptr || rating < 1 || rating > 5) {
        return false;
    }
    reviews_->save(Review(reviews_->nextId(), userId, productId, rating, comment));
    return true;
}

std::vector<Review> ReviewService::reviewsForProduct(int productId) const {
    if (reviews_ == nullptr) {
        return {};
    }
    return reviews_->findByProductId(productId);
}
