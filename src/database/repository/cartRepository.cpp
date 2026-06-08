#include "cartRepository.h"

Cart &CartRepository::cartForUser(int userId)
{
    return carts_[userId];
}

Cart CartRepository::cartForUser(int userId) const
{
    const auto found = carts_.find(userId);
    return found == carts_.end() ? Cart() : found->second;
}

void CartRepository::clear(int userId)
{
    carts_[userId].clear();
}
