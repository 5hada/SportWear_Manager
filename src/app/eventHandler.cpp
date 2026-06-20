#include "eventHandler.h"
#include "serviceProvider.h"

#include "model/product/category.h"

#include <algorithm>

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
            }
            break;
        case UserAction::Login:
            if (name != nullopt && password != nullopt) {
                return service.account.login(name.value(), password.value());
            }
            break;
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

ProductGridPageContent EventHandler::getProductsContents() {
    return service.ui.makeProductGridPageContent(
        service.search.getProducts(),
        service.search.getCurrentIndex(),
        service.search.getMaxIndex()
    );
}



bool EventHandler::setProduct(int productId) {
    return service.search.setCurrentProduct(productId);
}

int EventHandler::getCurrentProductId() {
    return service.search.getCurrentProduct().getId();
}

ProductDetailContent EventHandler::getProductDetailContent() {
    const auto product = service.search.getCurrentProduct();
    return service.ui.makeProductDetailContent(product, isWished(product.getId()));
}

ProductFormContent EventHandler::getProductFormContent() {
    return service.ui.makeProductFormContent(service.search.getCurrentProduct());
}

bool EventHandler::canManageProducts() {
    return getUser().getRole() == UiUserRole::Admin;
}

bool EventHandler::canUseCart() {
    return getUser().getRole() != UiUserRole::Guest;
}

bool EventHandler::setOrder(int productId) {
    if (productId == -1 && !canUseCart()) {
        return false;
    }
    const bool success = productId == -1
        ? service.order.makeListOrder(userId())
        : service.order.makeInstantOrder(userId(), productId);
    if (!success) {
        service.order.getClear();
    }
    return success;
}

OrderPanelContent EventHandler::getOrderPanelContent(int usedPoint) {
    return service.ui.makeOrderPanelContent(service.order.getOrder(), getOrderPayment(usedPoint));
}

int EventHandler::getOrderPayment(int usedPoint) {
    const auto order = service.order.getOrder();
    const int maxUsablePoint = std::min(order.getAvailablePoints(), order.getTotalPrice());
    if (usedPoint < 0) {
        usedPoint = 0;
    }
    if (usedPoint > maxUsablePoint) {
        usedPoint = maxUsablePoint;
    }
    return order.getTotalPrice() - usedPoint;
}

bool EventHandler::confirmOrder(int usedPoint) {
    return service.order.confirmOrder(userId(), usedPoint);
}


bool EventHandler::refund(int receiptId) {
    return service.order.refund(receiptId, userId());
}


Cart EventHandler::getCart() {
    if (!canUseCart()) {
        return Cart();
    }
    return service.cart.getCart(userId());
}

CartWidgetContent EventHandler::getCartWidgetContent() {
    return service.ui.makeCartWidgetContent(getCart());
}

CartPageContent EventHandler::getCartPageContent(int pageSize) {
    const Cart fullCart = getCart();
    const int maxPage = service.ui.pageMaxIndex(static_cast<int>(fullCart.getItems().size()), pageSize);
    const int cartPageIndex = service.page.getCartPageIndex(maxPage);
    return service.ui.makeCartPageContent(fullCart, cartPageIndex, pageSize);
}

CartPageContent EventHandler::moveCartPage(int delta, int pageSize) {
    const Cart fullCart = getCart();
    service.page.moveCartPage(delta, service.ui.pageMaxIndex(static_cast<int>(fullCart.getItems().size()), pageSize));
    return getCartPageContent(pageSize);
}

bool EventHandler::handleCart(CartAction action, int productId, int count, std::optional<bool> isSelected) {
    if (!canUseCart()) {
        return false;
    }
    return service.cart.handleCart(action, userId(), productId, count, isSelected);
}


ReceiptPageContent EventHandler::getReceiptPageContent(int pageSize) {
    const auto receipts = service.order.getReceipts(userId());
    const int maxPage = service.ui.pageMaxIndex(static_cast<int>(receipts.size()), pageSize);
    const int receiptPageIndex = service.page.getReceiptPageIndex(maxPage);
    return service.ui.makeReceiptPageContent(receipts, receiptPageIndex, pageSize);
}

ReceiptPageContent EventHandler::moveReceiptPage(int delta, int pageSize) {
    const auto receipts = service.order.getReceipts(userId());
    service.page.moveReceiptPage(delta, service.ui.pageMaxIndex(static_cast<int>(receipts.size()), pageSize));
    return getReceiptPageContent(pageSize);
}

WishPageContent EventHandler::getWishPageContent(int pageSize) {
    if (!canUseCart()) {
        return service.ui.makeWishPageContent(Products(), 0, pageSize);
    }
    const auto wishs = service.wish.getWishs(userId());
    const int maxPage = service.ui.pageMaxIndex(static_cast<int>(wishs.size()), pageSize);
    const int wishPageIndex = service.page.getWishPageIndex(maxPage);
    return service.ui.makeWishPageContent(wishs, wishPageIndex, pageSize);
}

WishPageContent EventHandler::moveWishPage(int delta, int pageSize) {
    if (!canUseCart()) {
        return service.ui.makeWishPageContent(Products(), 0, pageSize);
    }
    const auto wishs = service.wish.getWishs(userId());
    service.page.moveWishPage(delta, service.ui.pageMaxIndex(static_cast<int>(wishs.size()), pageSize));
    return getWishPageContent(pageSize);
}

bool EventHandler::isWished(int productId) {
    if (!canUseCart()) {
        return false;
    }
    for (const auto& product : service.wish.getWishs(userId())) {
        if (product.getId() == productId) {
            return true;
        }
    }
    return false;
}

bool EventHandler::setWish(int productId, bool isWished) {
    if (!canUseCart()) {
        return false;
    }
    return isWished
        ? service.wish.add(userId(), productId)
        : service.wish.remove(userId(), productId);
}

bool EventHandler::canWriteReview(int productId) {
    auto user = getUser();
    if (user.getRole() == UiUserRole::Admin) {
        return true;
    }
    if (user.getRole() == UiUserRole::Guest) {
        return false;
    }
    return hasPurchasedProduct(productId);
}

std::vector<int> EventHandler::getManageableReviewIds(int productId) {
    std::vector<int> ids;
    auto user = getUser();
    if (user.getRole() == UiUserRole::Guest) {
        return ids;
    }

    for (const auto& review : getReviews(productId)) {
        if (user.getRole() == UiUserRole::Admin || review.getUserId() == userId()) {
            ids.push_back(review.getId());
        }
    }
    return ids;
}

Reviews EventHandler::getReviews(int productId) {
    return service.review.getAllFromProduct(productId);
}

ReviewContent EventHandler::getReviewContent(int productId) {
    return service.ui.makeReviewContent(getReviews(productId), getManageableReviewIds(productId), canWriteReview(productId));
}

bool EventHandler::saveReview(int reviewId, int productId, int rating, const string& comment) {
    auto user = getUser();
    if (user.getRole() == UiUserRole::Guest || rating < 1 || rating > 5) {
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
    const bool canModify = user.getRole() == UiUserRole::Admin || existing->getUserId() == userId();
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
    if (user.getRole() == UiUserRole::Guest) {
        return false;
    }

    const auto existing = service.review.getById(reviewId);
    if (!existing.has_value()) {
        return false;
    }
    const bool canDelete = user.getRole() == UiUserRole::Admin || existing->getUserId() == userId();
    if (!canDelete) {
        return false;
    }
    return service.review.remove(reviewId);
}

bool EventHandler::updateProduct(Product product) {
    if (!canManageProducts()) {return false;}
    if (product.getId() <= 0) {
        return service.product.add(product);
    }
    return service.product.update(product);
}

bool EventHandler::updateProductForm(int productId, const string& name, Category category, int price, int stock, const string& detail) {
    Product product(
        Item{productId <= 0 ? 0 : productId, stock, price},
        name,
        category
    );
    product.setDetail(detail);
    return updateProduct(product);
}
