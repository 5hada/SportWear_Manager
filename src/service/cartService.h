#ifndef CARTSERVICE_H
#define CARTSERVICE_H

#include "database/repository/cartRepository.h"
#include "database/repository/productRepository.h"

class CartService {
public:
    CartService(CartRepository *carts, ProductRepository *products)
        : carts_(carts), products_(products)
    {
    }

    bool addProduct(int userId, int productId, int quantity)
    {
        if (carts_ == nullptr || products_ == nullptr || quantity <= 0) {
            return false;
        }

        auto product = products_->findById(productId);
        if (!product.has_value() || !product->hasStock(quantity)) {
            return false;
        }

        carts_->cartForUser(userId).addItem(*product, quantity);
        return true;
    }

    Cart cart(int userId) const
    {
        if (carts_ == nullptr) {
            return {};
        }
        return carts_->cartForUser(userId);
    }

    void clear(int userId)
    {
        if (carts_ != nullptr) {
            carts_->clear(userId);
        }
    }

private:
    CartRepository *carts_ = nullptr;
    ProductRepository *products_ = nullptr;
};

#endif // CARTSERVICE_H
