#include "database/repository/reviewRepository.h"
#include <optional>
#include <string>
#include <vector>

class ReviewService {
    ReviewRepository *reviewRepo = nullptr;

    bool isRepoValid() const;
public:
    explicit ReviewService(ReviewRepository *reviewRepo): reviewRepo(reviewRepo) {}

    bool add(int userId, int productId, int rating, const std::string &comment);
    bool update(const Review& review);
    bool remove(int reviewId);

    std::optional<Review> getById(int reviewId) const;
    std::vector<Review> getAllFromProduct(int productId) const;
};
