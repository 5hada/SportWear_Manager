#ifndef CARTREPOSITORY_H
#define CARTREPOSITORY_H

#include "model/cart/cart.h"

#include <map>

class CartRepository {
public:
    Cart &cartForUser(int userId) { return carts_[userId]; }
    const Cart &cartForUser(int userId) const { return carts_.at(userId); }

    void clear(int userId) { carts_[userId].clear(); }

private:
    std::map<int, Cart> carts_;
};

#endif // CARTREPOSITORY_H
