#include "cartService.h"
#include "database/repository/cartRepository.h"
#include "database/repository/productRepository.h"
#include "model/product/cartAction.h"
#include <optional>


Cart CartService::getCart(int userId) const {
    Cart cart;
    if (checkReposExist()) {
        cart = cartRepo->findByUser(userId);
        for (auto& item : cart.getItems()){
            item.setPrice(productRepo->findById(item.getId())->getPrice());
        }
    }
    return cart;
}

bool CartService::add(int userId, int productId, int count, std::optional<bool> isSelected) {
    if (count <= 0 || !checkProductExist(productId)) {return false;}
    int newCount = cartRepo->findByProduct(userId, productId).getCount() + count;
    if(isSelected == std::nullopt){
        return cartRepo->updateCount(userId, productId, newCount);
    }
    return cartRepo->update(userId, productId, newCount, isSelected.value());
}

bool CartService::sub(int userId, int productId, int count, std::optional<bool> isSelected){
    if (count <= 0 || !checkProductExist(productId)) {return false;}
    int newCount = cartRepo->findByProduct(userId, productId).getCount() - count;
    if(isSelected == std::nullopt){
        return cartRepo->updateCount(userId, productId, newCount);
    }
    return cartRepo->update(userId, productId, newCount, isSelected.value());
}

bool CartService::set(int userId, int productId, int count, std::optional<bool> isSelected) {
    if (count <= 0 || !checkProductExist(productId)) {return false;}
    if(isSelected == std::nullopt){
        return cartRepo->updateCount(userId, productId, count);
    }
    return cartRepo->update(userId, productId, count, isSelected.value());
}

bool CartService::toggle(int userId, int productId, std::optional<bool> isSelected) {
    if (!checkProductExist(productId)) {return false;}
    if (isSelected == std::nullopt) {return false;}
    return cartRepo->updateSelected(userId, productId, isSelected.value());
}

bool CartService::del(int userId, int productId) {
    return cartRepo->remove(userId, productId);
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



bool CartService::handleCart(CartAction action, int userId, int productId, int count, std::optional<bool> isSelected){
    if(!checkReposExist()){return false;}
    switch (action) {
        case CartAction::Add:
            return add(userId, productId, count, isSelected);
        case CartAction::Sub:
            return sub(userId, productId, count, isSelected);
        case CartAction::Set:
            return set(userId, productId, count, isSelected);
        case CartAction::Toggle:
            return toggle(userId, productId, isSelected);
        case CartAction::Del:
            return del(userId, productId);
        case CartAction::Clear:
            return clear(userId);
    }
    return false;
}