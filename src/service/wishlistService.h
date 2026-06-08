#ifndef WISHLISTSERVICE_H
#define WISHLISTSERVICE_H

#include "database/repository/wishlistRepository.h"

class WishlistService {
public:
    explicit WishlistService(WishlistRepository *wishlist) : wishlist_(wishlist) {}

    void add(int userId, int productId)
    {
        if (wishlist_ != nullptr) {
            wishlist_->add(userId, productId);
        }
    }

    bool remove(int userId, int productId)
    {
        return wishlist_ != nullptr && wishlist_->remove(userId, productId);
    }

private:
    WishlistRepository *wishlist_ = nullptr;
};

#endif // WISHLISTSERVICE_H
