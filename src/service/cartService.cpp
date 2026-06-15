#include "cartService.h"
#include "database/repository/cartRepository.h"
#include "database/repository/productRepository.h"
#include "model/product/cartAction.h"


Cart CartService::getCart(int userId) const {
    if (!checkReposExist()) { return Cart(); }
    Cart cart = cartRepo->getCart(userId);
    for (auto& item : cart.getItems()){
        item.setPrice(productRepo->findById(userId)->getPrice());
    }
    return cart;
}

bool CartService::add(int userId, int productId, int count) {
    if (count <= 0 || !checkProductExist(productId)){
        return false;
    }
    return cartRepo->updateItem(userId, productId, count);
}

bool CartService::sub(int userId, int productId, int count){
    if (count <= 0 || !checkProductExist(productId)){
        return false;
    }
    return cartRepo->updateItem(userId, productId, count);
}

bool CartService::set(int userId, int productId, int count) {
    if (count <= 0 || !checkProductExist(productId)){
        return false;
    }
    return cartRepo->updateItem(userId, productId, count);
}

bool CartService::del(int userId, int productId) {
    return cartRepo->removeItem(userId, productId);
}

bool CartService::clear(int userId) {
    return cartRepo->clear(userId);
}



bool CartService::checkReposExist() const{
    return !(cartRepo == nullptr || productRepo == nullptr);
}

bool CartService::checkProductExist(int productId) const{
    auto product = productRepo->findById(productId);
    return product.has_value();
}



bool CartService::handleCart(CartAction action, int userId, int productId, int count){
    if(!checkReposExist()){return false;}
    switch (action) {
        case CartAction::Add:
            return add(userId, productId, count);
        case CartAction::Sub:
            return sub(userId, productId, count);
        case CartAction::Set:
            return set(userId, productId, count);
        case CartAction::Del:
            return del(userId, productId);
        case CartAction::Clear:
            return clear(userId);
    }
    return false;
}