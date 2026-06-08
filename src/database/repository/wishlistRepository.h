#ifndef WISHLISTREPOSITORY_H
#define WISHLISTREPOSITORY_H

#include <algorithm>
#include <map>
#include <vector>

class WishlistRepository {
public:
    std::vector<int> findProductIds(int userId) const;
    void add(int userId, int productId);
    bool remove(int userId, int productId);

private:
    std::map<int, std::vector<int>> wishlists_;
};

#endif // WISHLISTREPOSITORY_H
