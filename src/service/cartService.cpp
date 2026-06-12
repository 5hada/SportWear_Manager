#include "cartService.h"

CartService::CartService(CartRepository *carts, ProductRepository *products)
    : carts_(carts), products_(products) {}

bool CartService::addProduct(int userId, int productId, int quantity) {
    if (carts_ == nullptr || products_ == nullptr || quantity <= 0) {
        return false;
    }

    auto product = products_->findById(productId);
    if (!product.has_value() || !product->hasStock(quantity)) {
        return false;
    }

    carts_->addItem(userId, productId, quantity);
    return true;
}

bool CartService::removeProduct(int userId, int productId) {
    if (carts_ == nullptr) {
        return false;
    }
    return carts_->removeItem(userId, productId);
}

Cart CartService::cart(int userId) const {
    if (carts_ == nullptr) {
        return {};
    }
    return carts_->getCart(userId);
}

void CartService::clear(int userId) {
    if (carts_ != nullptr) {
        carts_->clear(userId);
    }
}
