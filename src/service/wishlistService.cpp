#include "wishlistService.h"

WishlistService::WishlistService(WishlistRepository *wishlist) : wishlist_(wishlist) {}

void WishlistService::add(int userId, int productId)
{
    if (wishlist_ != nullptr) {
        wishlist_->add(userId, productId);
    }
}

bool WishlistService::remove(int userId, int productId)
{
    return wishlist_ != nullptr && wishlist_->remove(userId, productId);
}
