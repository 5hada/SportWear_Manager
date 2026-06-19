#include "eventHandler.h"
#include "model/actions.h"
#include "serviceProvider.h"
#include "model/product/category.h"
#include <optional>

int EventHandler::userId() {
    return service.account.getUserId();
}

UserInfo EventHandler::getUser() {
    return service.account.getInfo();
}

bool EventHandler::setUser(UserAction action, optional<string> name, optional<string> password) {
    switch (action) {
        case UserAction::Signup:
            if (name != nullopt && password != nullopt) {
                return service.account.signup(name.value(), password.value());
                break;
            }
        case UserAction::Login:
            if (name != nullopt && password != nullopt) {
                return service.account.login(name.value(), password.value());
                break;
            }
        case UserAction::Logout:
            return service.account.logout();
    }
    return false;
}



bool EventHandler::setProducts(int index, optional<string> keyword, optional<Category> category) {
    if (index == -1 && keyword == nullopt && category == nullopt) {return false;}
    if (category != nullopt) {
        if (category == Category::Unknown) {
            if(!service.search.setProductsPool()) {return false;}
        }
        else {
            if (!service.search.setProductsPool(category.value())) {return false;}
        }
    }
    if (keyword != nullopt) {
        if (!service.search.searchProducts(keyword.value())) {return false;}
    }
    if (index != -1) {
        if (!service.search.setCurrentIndex(index)) {return false;}
    }
    return true;

}

std::tuple<Products, int, int> EventHandler::getProductsContents() {
    return std::make_tuple(service.search.getProducts(), service.search.getCurrentIndex(), service.search.getMaxIndex());
}



bool EventHandler::setProduct(int productId) {
    return service.search.setCurrentProduct(productId);
}
Product EventHandler::getProduct() {
    return service.search.getCurrentProduct();
}

bool EventHandler::setOrder(int productId) {
    if (productId == -1) {
        if (service.order.makeListOrder(userId())) {
            return true;
        }
    }
    else {
        if (service.order.makeInstantOrder(userId(), productId)) {
            return true;
        }
    }
    service.order.getClear();
    return false;

}

Order EventHandler::getOrder() {
    return service.order.getOrder();
}

bool EventHandler::confirmOrder(int usedPoint) {
    return service.order.confirmOrder(userId(), usedPoint);
}


bool EventHandler::refund(int receiptId) {
    return service.order.refund(receiptId, userId());
}


Cart EventHandler::getCart() {
    return service.cart.getCart(userId());
}
bool EventHandler::handleCart(CartAction action, int productId, int count, std::optional<bool> isSelected) {
    return service.cart.handleCart(action, userId(), productId, count, isSelected);
}


Receipts EventHandler::getReceipts() {
    return service.order.getReceipts(userId());
}


Products EventHandler::getWishs() {
    return service.wish.getWishs(userId());
}

bool EventHandler::isWished(int productId) {
    for (const auto& product : getWishs()) {
        if (product.getId() == productId) {
            return true;
        }
    }
    return false;
}

bool EventHandler::setWish(int productId, bool isWished) {
    if (isWished) {
        return service.wish.add(userId(), productId);
    }
    else {
        return service.wish.remove(userId(), productId);
    }
}


Reviews EventHandler::getReviews(int productId) {
    return service.review.getAllFromProduct(productId);
}
bool EventHandler::setReview(Review review) {
    return false;
}


bool EventHandler::updateProduct(Product product) {
    return false;
}
