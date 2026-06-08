#ifndef REVIEWREPOSITORY_H
#define REVIEWREPOSITORY_H

#include "model/review.h"

#include <vector>

class ReviewRepository {
public:
    const std::vector<Review> &findAll() const { return reviews_; }

    std::vector<Review> findByProductId(int productId) const
    {
        std::vector<Review> result;
        for (const auto &review : reviews_) {
            if (review.productId() == productId) {
                result.push_back(review);
            }
        }
        return result;
    }

    void save(const Review &review) { reviews_.push_back(review); }
    int nextId() const { return static_cast<int>(reviews_.size()) + 1; }

private:
    std::vector<Review> reviews_;
};

#endif // REVIEWREPOSITORY_H
