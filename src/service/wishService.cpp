#include "wishService.h"

#include "database/repository/productRepository.h"
#include "database/repository/wishRepository.h"

bool WishService::add(int userId, int productId) {
    if (!isRepoValid()){return false;}
    if (productRepo->findById(productId) == std::nullopt){return false;}
    wishRepo->insert(userId, productId);
    return true;
}

bool WishService::remove(int userId, int productId) {
    if (!isRepoValid()){return false;}
    return wishRepo->remove(userId, productId);
}

bool WishService::isRepoValid() {
    return wishRepo != nullptr && productRepo != nullptr;
}
