#ifndef WISHLISTSERVICE_H
#define WISHLISTSERVICE_H

#include "database/repository/wishlistRepository.h"

class WishlistService {
public:
    explicit WishlistService(WishlistRepository *wishlist);

    void add(int userId, int productId);
    bool remove(int userId, int productId);

private:
    WishlistRepository *wishlist_ = nullptr;
};

#endif // WISHLISTSERVICE_H
