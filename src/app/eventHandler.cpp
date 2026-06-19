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

std::tuple<const Products&, int, int> EventHandler::getProductsContents(optional<string> text, optional<Category> category) {
    if (text == nullopt && category == nullopt) {
        return std::make_tuple(service.product.getAll(), 0, 0);
    }
    if (category != nullopt) {
        return std::make_tuple(service.product.getByCategory(category.value()), 0, 0);
    }
    return std::make_tuple(service.product.getAll(), 0, 0);
}
Product EventHandler::getProduct(int productId) {
    return service.product.getById(productId);
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
