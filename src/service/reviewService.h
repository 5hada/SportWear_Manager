#include "database/repository/reviewRepository.h"
#include <string>
#include <vector>

class ReviewService {
    ReviewRepository *reviews_ = nullptr;

public:
    explicit ReviewService(ReviewRepository *reviews);

    bool addReview(int userId, int productId, int rating, const std::string &comment);
    std::vector<Review> reviewsForProduct(int productId) const;
};
