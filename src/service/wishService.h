#include "database/repository/wishRepository.h"

class WishService {
    WishRepository *wishlist = nullptr;
    
public:
    explicit WishService(WishRepository *wishlist);

    void add(int userId, int productId);
    bool remove(int userId, int productId);
};
