#include "reviewRepository.h"

const std::vector<Review> &ReviewRepository::findAll() const
{
    return reviews_;
}

std::vector<Review> ReviewRepository::findByProductId(int productId) const
{
    std::vector<Review> result;
    for (const auto &review : reviews_) {
        if (review.productId() == productId) {
            result.push_back(review);
        }
    }
    return result;
}

void ReviewRepository::save(const Review &review)
{
    reviews_.push_back(review);
}

int ReviewRepository::nextId() const
{
    return static_cast<int>(reviews_.size()) + 1;
}
