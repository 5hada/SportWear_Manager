#include "database/repository/wishlistRepository.h"

class WishlistService {
    WishlistRepository *wishlist_ = nullptr;
    
public:
    explicit WishlistService(WishlistRepository *wishlist);

    void add(int userId, int productId);
    bool remove(int userId, int productId);
};
