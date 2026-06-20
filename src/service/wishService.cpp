#include "wishService.h"

#include "database/repository/productRepository.h"
#include "database/repository/wishRepository.h"

using std::nullopt;

Products WishService::getWishs(int userId){
    Products wishs;
    optional<Product> item;
    if (userId > 0 && isRepoValid()){
        for(int id: wishRepo->findByUser(userId)){
            item = productRepo->findById(id);
            if (item != nullopt){
                wishs.emplace_back(item.value());
            }
        }

    }
    return wishs;
}

bool WishService::add(int userId, int productId) {
    if (!isRepoValid()){return false;}
    if (userId <= 0) {return false;}
    if (productRepo->findById(productId) == nullopt){return false;}
    return wishRepo->insert(userId, productId);
}

bool WishService::remove(int userId, int productId) {
    if (!isRepoValid()){return false;}
    if (userId <= 0) {return false;}
    return wishRepo->remove(userId, productId);
}

bool WishService::isRepoValid() {
    return wishRepo != nullptr && productRepo != nullptr;
}
