#include "reviewService.h"

bool ReviewService::add(int userId, int productId, int rating, const string &comment) {
    if (!isRepoValid()|| rating < 1 || rating > 5) {
        return false;
    }
    return reviewRepo->insert(Review(reviewRepo->nextId(), userId, productId, rating, comment));
}

bool ReviewService::update(const Review& review) {
    if (!isRepoValid() || review.getId() <= 0 || review.getRating() < 1 || review.getRating() > 5) {
        return false;
    }
    return reviewRepo->update(review);
}

bool ReviewService::remove(int reviewId) {
    if (!isRepoValid() || reviewId <= 0) {
        return false;
    }
    return reviewRepo->remove(reviewId);
}

optional<Review> ReviewService::getById(int reviewId) const {
    if (!isRepoValid()) {return std::nullopt;}
    return reviewRepo->findById(reviewId);
}

Reviews ReviewService::getAllFromProduct(int productId) const {
    if (!isRepoValid()) {return {};}
    return reviewRepo->findByProductId(productId);
}


bool ReviewService::isRepoValid() const{
    return reviewRepo != nullptr;
}
