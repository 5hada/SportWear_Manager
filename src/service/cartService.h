#ifndef CARTSERVICE_H
#define CARTSERVICE_H

#include "database/repository/cartRepository.h"
#include "database/repository/productRepository.h"

class CartService {
public:
    CartService(CartRepository *carts, ProductRepository *products);

    bool addProduct(int userId, int productId, int quantity);
    bool removeProduct(int userId, int productId);
    Cart cart(int userId) const;
    void clear(int userId);

private:
    CartRepository *carts_ = nullptr;
    ProductRepository *products_ = nullptr;
};

#endif // CARTSERVICE_H
