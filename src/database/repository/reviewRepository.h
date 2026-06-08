#ifndef REVIEWREPOSITORY_H
#define REVIEWREPOSITORY_H

#include "model/review.h"

#include <vector>

class ReviewRepository {
public:
    const std::vector<Review> &findAll() const;
    std::vector<Review> findByProductId(int productId) const;
    void save(const Review &review);
    int nextId() const;

private:
    std::vector<Review> reviews_;
};

#endif // REVIEWREPOSITORY_H
