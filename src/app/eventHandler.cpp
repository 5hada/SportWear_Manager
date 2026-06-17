#include "eventHandler.h"
#include "model/actions.h"
#include "serviceProvider.h"
#include "model/product/category.h"

int EventHandler::userId() {
    return service.account.getUserId();
}

UserInfo EventHandler::getUser() {
    return service.account.getInfo();
}

bool EventHandler::setUser(UserAction action, optional<string> name, optional<string> password) {
    switch (action) {
        case UserAction::Signup:
            if (name == nullopt || password == nullopt) {
                return service.account.signup(name.value(), password.value());
                break;
            }
        case UserAction::Login:
            if (name == nullopt || password == nullopt) {
                return service.account.login(name.value(), password.value());
                break;
            }
        case UserAction::Logout:
            return service.account.logout();
    }
    return false;
}

Products EventHandler::getProducts(optional<string> text, optional<Category> category) {
    if (text == nullopt && category == nullopt) {
        return service.product.getAll();
    }
    return service.product.getAll(); //임시
}
Product EventHandler::getProduct(int productId) {
    return service.product.getById(productId);
}

Order EventHandler::getOrder(int productId) {
    if (productId < 0) {
        if (service.order.makeListOrder(userId())) {
            return service.order.getOrder();
        }
    }
    else {
        if (service.order.makeInstantOrder(productId)) {
            return service.order.getOrder();
        }
    }
    return service.order.getClear();
}
bool EventHandler::confirmOrder(long long usedPoint) {
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


bool EventHandler::setProduct() {
    return false;
}
