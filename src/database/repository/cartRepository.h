#include "model/cart/cart.h"
#include <map>

class CartRepository {
    std::map<int, Cart> carts_;

public:
    Cart &cartForUser(int userId);
    Cart cartForUser(int userId) const;

    void clear(int userId);
};
