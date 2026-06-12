#include <algorithm>
#include <map>
#include <vector>

class WishlistRepository {
    std::map<int, std::vector<int>> wishlists_;

public:
    std::vector<int> findProductIds(int userId) const;
    void add(int userId, int productId);
    bool remove(int userId, int productId);
};
