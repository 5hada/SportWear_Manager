#include "model/review.h"
#include <vector>

class ReviewRepository {
    std::vector<Review> reviews_;

public:
    const std::vector<Review> &findAll() const;
    std::vector<Review> findByProductId(int productId) const;
    void save(const Review &review);
    int nextId() const;
};
