#include "database/repository/reviewRepository.h"

class ReviewService {
    ReviewRepository *reviewRepo = nullptr;

    bool isRepoValid() const;
public:
    explicit ReviewService(ReviewRepository *reviewRepo): reviewRepo(reviewRepo) {}

    bool add(int userId, int productId, int rating, const string &comment);
    bool update(const Review& review);
    bool remove(int reviewId);

    optional<Review> getById(int reviewId) const;
    Reviews getAllFromProduct(int productId) const;
};
