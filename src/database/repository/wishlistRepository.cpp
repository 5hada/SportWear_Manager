#include "wishlistRepository.h"

#include <algorithm>

std::vector<int> WishlistRepository::findProductIds(int userId) const
{
    const auto found = wishlists_.find(userId);
    return found == wishlists_.end() ? std::vector<int>() : found->second;
}

void WishlistRepository::add(int userId, int productId)
{
    auto &list = wishlists_[userId];
    if (std::find(list.begin(), list.end(), productId) == list.end()) {
        list.push_back(productId);
    }
}

bool WishlistRepository::remove(int userId, int productId)
{
    auto &list = wishlists_[userId];
    const auto originalSize = list.size();
    list.erase(std::remove(list.begin(), list.end(), productId), list.end());
    return list.size() != originalSize;
}
