#pragma once

class PageService {
    int wishPageIndex = 0;
    int cartPageIndex = 0;
    int receiptPageIndex = 0;

    static void movePageIndex(int& pageIndex, int delta, int maxPageIndex);
    static void clampPageIndex(int& pageIndex, int maxPageIndex);

public:
    int getWishPageIndex(int maxPageIndex);
    int moveWishPage(int delta, int maxPageIndex);

    int getCartPageIndex(int maxPageIndex);
    int moveCartPage(int delta, int maxPageIndex);

    int getReceiptPageIndex(int maxPageIndex);
    int moveReceiptPage(int delta, int maxPageIndex);
};
