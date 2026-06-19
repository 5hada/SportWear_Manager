#include "eventHandler.h"
#include "model/actions.h"
#include "serviceProvider.h"
#include "model/product/category.h"
#include <algorithm>
#include <optional>
#include <sstream>

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

int EventHandler::pageMaxIndex(int totalCount, int pageSize) const {
    if (pageSize <= 0 || totalCount <= 0) {
        return 0;
    }
    return (totalCount - 1) / pageSize;
}

void EventHandler::movePageIndex(int& pageIndex, int delta, int maxPageIndex) {
    pageIndex += delta;
    if (pageIndex < 0) {
        pageIndex = 0;
    }
    if (pageIndex > maxPageIndex) {
        pageIndex = maxPageIndex;
    }
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

bool EventHandler::canManageProducts() {
    return getUser().getRole() == UserRole::Admin;
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

int EventHandler::getOrderTotalPrice() {
    return getOrder().getTotalPrice();
}

int EventHandler::getOrderAvailablePoints() {
    return getOrder().getAvailablePoints();
}

int EventHandler::getOrderMaxUsablePoint() {
    const auto order = getOrder();
    return std::min(order.getAvailablePoints(), order.getTotalPrice());
}

int EventHandler::getOrderPayment(int usedPoint) {
    const auto order = getOrder();
    const int maxUsablePoint = getOrderMaxUsablePoint();
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
    return service.cart.getCart(userId());
}

CartPageContent EventHandler::getCartPageContent(int pageSize) {
    const Cart fullCart = getCart();
    Cart pageCart;
    pageCart.setUserId(fullCart.getUserId());
    const int maxPage = pageMaxIndex(static_cast<int>(fullCart.getItems().size()), pageSize);
    if (cartPageIndex > maxPage) {
        cartPageIndex = maxPage;
    }

    CartItems pageItems;
    const int begin = cartPageIndex * pageSize;
    const int end = std::min(begin + pageSize, static_cast<int>(fullCart.getItems().size()));
    for (int index = begin; index < end; ++index) {
        pageItems.push_back(fullCart.getItems()[index]);
    }
    pageCart.setItems(pageItems);

    CartPageContent content;
    content.cart = pageCart;
    content.currentPage = cartPageIndex;
    content.maxPage = maxPage;
    content.totalCount = fullCart.getTotalCount();
    content.totalPrice = fullCart.getTotalPrice();
    for (const auto& item : pageCart.getItems()) {
        const auto product = service.product.getById(item.id);
        content.productNames.push_back(product.getName().empty() ? "Unknown" : product.getName());
        content.itemTotals.push_back(item.price * item.count);
    }
    return content;
}

CartPageContent EventHandler::moveCartPage(int delta, int pageSize) {
    const Cart fullCart = getCart();
    movePageIndex(cartPageIndex, delta, pageMaxIndex(static_cast<int>(fullCart.getItems().size()), pageSize));
    return getCartPageContent(pageSize);
}

bool EventHandler::handleCart(CartAction action, int productId, int count, std::optional<bool> isSelected) {
    return service.cart.handleCart(action, userId(), productId, count, isSelected);
}


Receipts EventHandler::getReceipts() {
    return service.order.getReceipts(userId());
}

ReceiptPageContent EventHandler::getReceiptPageContent(int pageSize) {
    const auto receipts = getReceipts();
    const int maxPage = pageMaxIndex(static_cast<int>(receipts.size()), pageSize);
    if (receiptPageIndex > maxPage) {
        receiptPageIndex = maxPage;
    }

    ReceiptPageContent content;
    content.currentPage = receiptPageIndex;
    content.maxPage = maxPage;
    const int begin = receiptPageIndex * pageSize;
    const int end = std::min(begin + pageSize, static_cast<int>(receipts.size()));
    for (int index = begin; index < end; ++index) {
        content.receipts.push_back(receipts[index]);
        content.itemSummaries.push_back(getReceiptItemSummary(receipts[index]));
        content.refundable.push_back(!receipts[index].getIsCanceled());
    }
    return content;
}

ReceiptPageContent EventHandler::moveReceiptPage(int delta, int pageSize) {
    const auto receipts = getReceipts();
    movePageIndex(receiptPageIndex, delta, pageMaxIndex(static_cast<int>(receipts.size()), pageSize));
    return getReceiptPageContent(pageSize);
}


Products EventHandler::getWishs() {
    return service.wish.getWishs(userId());
}

WishPageContent EventHandler::getWishPageContent(int pageSize) {
    const auto wishs = getWishs();
    const int maxPage = pageMaxIndex(static_cast<int>(wishs.size()), pageSize);
    if (wishPageIndex > maxPage) {
        wishPageIndex = maxPage;
    }

    WishPageContent content;
    content.currentPage = wishPageIndex;
    content.maxPage = maxPage;
    const int begin = wishPageIndex * pageSize;
    const int end = std::min(begin + pageSize, static_cast<int>(wishs.size()));
    for (int index = begin; index < end; ++index) {
        content.products.push_back(wishs[index]);
    }
    return content;
}

WishPageContent EventHandler::moveWishPage(int delta, int pageSize) {
    const auto wishs = getWishs();
    movePageIndex(wishPageIndex, delta, pageMaxIndex(static_cast<int>(wishs.size()), pageSize));
    return getWishPageContent(pageSize);
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

std::vector<int> EventHandler::getManageableReviewIds(int productId) {
    std::vector<int> ids;
    auto user = getUser();
    if (user.getRole() == UserRole::Guest) {
        return ids;
    }

    for (const auto& review : getReviews(productId)) {
        if (user.getRole() == UserRole::Admin || review.getUserId() == userId()) {
            ids.push_back(review.getId());
        }
    }
    return ids;
}

string EventHandler::getReviewSummary(int productId) {
    const auto reviews = getReviews(productId);
    if (reviews.empty()) {
        return "No reviews yet.";
    }

    int ratingSum = 0;
    for (const auto& review : reviews) {
        ratingSum += review.getRating();
    }
    const double average = static_cast<double>(ratingSum) / static_cast<double>(reviews.size());

    std::ostringstream out;
    out.setf(std::ios::fixed);
    out.precision(1);
    out << reviews.size() << " reviews - Average " << average << " / 5";
    return out.str();
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

string EventHandler::getReceiptItemSummary(const Receipt& receipt) {
    const auto items = receipt.getOrderItems();
    if (items.empty()) {
        return "No items";
    }

    int quantity = 0;
    for (const auto& item : items) {
        quantity += item.count;
    }

    const auto& first = items.front();
    std::ostringstream out;
    out << "Product #" << first.id << " x" << first.count;
    if (items.size() > 1) {
        out << " + " << (items.size() - 1) << " more";
    }
    out << " (" << quantity << " total)";
    return out.str();
}
