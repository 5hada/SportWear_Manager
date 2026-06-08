#include "cartService.h"

CartService::CartService(CartRepository *carts, ProductRepository *products)
    : carts_(carts), products_(products)
{
}

bool CartService::addProduct(int userId, int productId, int quantity)
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

bool CartService::removeProduct(int userId, int productId)
{
    if (carts_ == nullptr) {
        return false;
    }
    return carts_->cartForUser(userId).removeItem(productId);
}

Cart CartService::cart(int userId) const
{
    if (carts_ == nullptr) {
        return {};
    }
    return carts_->cartForUser(userId);
}

void CartService::clear(int userId)
{
    if (carts_ != nullptr) {
        carts_->clear(userId);
    }
}
