#include "eventHandler.h"
#include "model/product/category.h"
#include "serviceProvider.h"

int EventHandler::userId() {
    return service.account.getUserId();
}

bool EventHandler::signup(string name, string password) {
    return service.account.signup(name, password);
}

bool EventHandler::login(string name, string password) {
    return service.account.login(name, password);
}

bool EventHandler::logout() {
    return service.account.logout();
}

string EventHandler::getName() {
    return service.account.getUserName();
}
int EventHandler::getPoint() {
    return service.point.getPoint(userId());
}

Cart EventHandler::getCart() {
    return service.cart.getCart(userId());
}
bool EventHandler::handleCart(CartAction action, int productId, int count) {
    return service.cart.handleCart(action, userId(), productId, count);
}

Receipts EventHandler::getReceipts() {
    return service.order.getReceipts(userId());
}
bool EventHandler::refund(int receiptId) {
    return service.order.refund(receiptId);
}

Products EventHandler::getAll() {
    return service.product.getAll();
}
Products EventHandler::getCategory(Category category) {
    return {};
}
Products EventHandler::getWishAll() {
    return service.wish.getWishs(userId());
}
Product EventHandler::getProduct(int productId) {
    return service.product.getById(productId);
}

bool EventHandler::setWish(int productId) {
    return service.wish.add(userId(), productId);
}