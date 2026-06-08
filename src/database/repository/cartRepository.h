#ifndef CARTREPOSITORY_H
#define CARTREPOSITORY_H

#include "model/cart/cart.h"

#include <map>

class CartRepository {
public:
    Cart &cartForUser(int userId);
    Cart cartForUser(int userId) const;

    void clear(int userId);

private:
    std::map<int, Cart> carts_;
};

#endif // CARTREPOSITORY_H
