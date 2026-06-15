#include "database/repository/reviewRepository.h"
#include <string>
#include <vector>

class ReviewService {
    ReviewRepository *reviewRepo = nullptr;

    bool isRepoValid() const;
public:
    explicit ReviewService(ReviewRepository *reviewRepo): reviewRepo(reviewRepo) {}

    bool add(int userId, int productId, int rating, const std::string &comment);
    // bool modify(int userId, int productId, int rating, const std::string &comment);
    // bool remove(int userId, int productId, int rating, const std::string &comment);

    std::vector<Review> getAllFromProduct(int productId) const;
};
