#include "pageService.h"

void PageService::movePageIndex(int& pageIndex, int delta, int maxPageIndex) {
    pageIndex += delta;
    clampPageIndex(pageIndex, maxPageIndex);
}

void PageService::clampPageIndex(int& pageIndex, int maxPageIndex) {
    if (pageIndex < 0) {
        pageIndex = 0;
    }
    if (pageIndex > maxPageIndex) {
        pageIndex = maxPageIndex;
    }
}

int PageService::getWishPageIndex(int maxPageIndex) {
    clampPageIndex(wishPageIndex, maxPageIndex);
    return wishPageIndex;
}

int PageService::moveWishPage(int delta, int maxPageIndex) {
    movePageIndex(wishPageIndex, delta, maxPageIndex);
    return wishPageIndex;
}

int PageService::getCartPageIndex(int maxPageIndex) {
    clampPageIndex(cartPageIndex, maxPageIndex);
    return cartPageIndex;
}

int PageService::moveCartPage(int delta, int maxPageIndex) {
    movePageIndex(cartPageIndex, delta, maxPageIndex);
    return cartPageIndex;
}

int PageService::getReceiptPageIndex(int maxPageIndex) {
    clampPageIndex(receiptPageIndex, maxPageIndex);
    return receiptPageIndex;
}

int PageService::moveReceiptPage(int delta, int maxPageIndex) {
    movePageIndex(receiptPageIndex, delta, maxPageIndex);
    return receiptPageIndex;
}
