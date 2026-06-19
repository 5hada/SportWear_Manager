#include "eventHandler.h"
#include "model/actions.h"
#include "serviceProvider.h"
#include "model/product/category.h"
#include <optional>

int EventHandler::userId() {
    return service.account.getUserId();
}

bool EventHandler::hasPurchasedProduct(int productId) {
    if (userId() <= 0) {return false;}
    for (const auto& receipt : service.order.getReceipts(userId())) {
        if (receipt.getIsCanceled()) {
            continue;
        }
        for (const auto& item : receipt.getOrderItems()) {
            if (item.id == productId) {
                return true;
            }
        }
    }
    return false;
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


int EventHandler::getUserId() {
    return userId();
}

bool EventHandler::canWriteReview(int productId) {
    auto user = getUser();
    if (user.getRole() == UserRole::Admin) {
        return true;
    }
    if (user.getRole() == UserRole::Guest) {
        return false;
    }
    return hasPurchasedProduct(productId);
}

Reviews EventHandler::getReviews(int productId) {
    return service.review.getAllFromProduct(productId);
}

bool EventHandler::saveReview(int reviewId, int productId, int rating, const string& comment) {
    auto user = getUser();
    if (user.getRole() == UserRole::Guest || rating < 1 || rating > 5) {
        return false;
    }

    if (reviewId <= 0) {
        if (!canWriteReview(productId)) {
            return false;
        }
        return service.review.add(userId(), productId, rating, comment);
    }

    const auto existing = service.review.getById(reviewId);
    if (!existing.has_value()) {
        return false;
    }
    const bool canModify = user.getRole() == UserRole::Admin || existing->getUserId() == userId();
    if (!canModify) {
        return false;
    }
    return service.review.update(Review(
        existing->getId(),
        existing->getUserId(),
        existing->getProductId(),
        rating,
        comment
    ));
}

bool EventHandler::deleteReview(int reviewId) {
    auto user = getUser();
    if (user.getRole() == UserRole::Guest) {
        return false;
    }

    const auto existing = service.review.getById(reviewId);
    if (!existing.has_value()) {
        return false;
    }
    const bool canDelete = user.getRole() == UserRole::Admin || existing->getUserId() == userId();
    if (!canDelete) {
        return false;
    }
    return service.review.remove(reviewId);
}

bool EventHandler::setReview(Review review) {
    return saveReview(review.getId(), review.getProductId(), review.getRating(), review.getComment());
}


bool EventHandler::updateProduct(Product product) {
    if (getUser().getRole() != UserRole::Admin) {return false;}
    if (product.getId() <= 0) {
        return service.product.add(product);
    }
    return service.product.update(product);
}
