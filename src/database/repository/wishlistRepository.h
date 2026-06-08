#ifndef WISHLISTREPOSITORY_H
#define WISHLISTREPOSITORY_H

#include <algorithm>
#include <map>
#include <vector>

class WishlistRepository {
public:
    const std::vector<int> &findProductIds(int userId) const { return wishlists_.at(userId); }

    void add(int userId, int productId)
    {
        auto &list = wishlists_[userId];
        if (std::find(list.begin(), list.end(), productId) == list.end()) {
            list.push_back(productId);
        }
    }

    bool remove(int userId, int productId)
    {
        auto &list = wishlists_[userId];
        const auto originalSize = list.size();
        list.erase(std::remove(list.begin(), list.end(), productId), list.end());
        return list.size() != originalSize;
    }

private:
    std::map<int, std::vector<int>> wishlists_;
};

#endif // WISHLISTREPOSITORY_H
