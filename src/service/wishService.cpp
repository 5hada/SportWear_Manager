#include "wishService.h"

#include "database/repository/productRepository.h"
#include "database/repository/wishRepository.h"
#include <optional>

std::vector<Product> WishService::getWishs(int userId){
    std::vector<Product> wishs;
    std::optional<Product> item;
    if (userId > 1){
        for(int id: wishRepo->findByUser(userId)){
            item = productRepo->findById(id);
            if (item != std::nullopt){
                wishs.emplace_back(item.value());
            }
        }

    }
    return wishs;
}

bool WishService::add(int userId, int productId) {
    if (!isRepoValid()){return false;}
    if (productRepo->findById(productId) == std::nullopt){return false;}
    return wishRepo->insert(userId, productId);
}

bool WishService::remove(int userId, int productId) {
    if (!isRepoValid()){return false;}
    return wishRepo->remove(userId, productId);
}

bool WishService::isRepoValid() {
    return wishRepo != nullptr && productRepo != nullptr;
}
