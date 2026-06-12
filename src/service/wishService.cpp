#include "wishService.h"

WishService::WishService(WishRepository *wishlist)
    : wishlist(wishlist) {}

void WishService::add(int userId, int productId) {
    if (wishlist != nullptr) {
        wishlist->add(userId, productId);
    }
}

bool WishService::remove(int userId, int productId) {
    return wishlist != nullptr && wishlist->remove(userId, productId);
}
