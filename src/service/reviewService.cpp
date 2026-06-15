#include "reviewService.h"

bool ReviewService::add(int userId, int productId, int rating, const std::string &comment) {
    if (!isRepoValid()|| rating < 1 || rating > 5) {
        return false;
    }
    reviewRepo->insert(Review(reviewRepo->nextId(), userId, productId, rating, comment));
    return true;
}

std::vector<Review> ReviewService::getAllFromProduct(int productId) const {
    if (!isRepoValid()) {return {};}
    return reviewRepo->findByProductId(productId);
}


bool ReviewService::isRepoValid() const{
    return reviewRepo != nullptr;
}