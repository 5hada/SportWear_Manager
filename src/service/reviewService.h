#ifndef REVIEWSERVICE_H
#define REVIEWSERVICE_H

#include "database/repository/reviewRepository.h"

class ReviewService {
public:
    explicit ReviewService(ReviewRepository *reviews) : reviews_(reviews) {}

    bool addReview(int userId, int productId, int rating, const std::string &comment)
    {
        if (reviews_ == nullptr || rating < 1 || rating > 5) {
            return false;
        }
        reviews_->save(Review(reviews_->nextId(), userId, productId, rating, comment));
        return true;
    }

    std::vector<Review> reviewsForProduct(int productId) const
    {
        if (reviews_ == nullptr) {
            return {};
        }
        return reviews_->findByProductId(productId);
    }

private:
    ReviewRepository *reviews_ = nullptr;
};

#endif // REVIEWSERVICE_H
