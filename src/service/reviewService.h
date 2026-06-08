#ifndef REVIEWSERVICE_H
#define REVIEWSERVICE_H

#include "database/repository/reviewRepository.h"

#include <string>
#include <vector>

class ReviewService {
public:
    explicit ReviewService(ReviewRepository *reviews);

    bool addReview(int userId, int productId, int rating, const std::string &comment);
    std::vector<Review> reviewsForProduct(int productId) const;

private:
    ReviewRepository *reviews_ = nullptr;
};

#endif // REVIEWSERVICE_H
