#pragma once

#include "model/product/cart.h"
#include "model/product/order.h"
#include "model/product/product.h"
#include "model/product/receipt.h"
#include "model/review.h"
#include "model/ui/cartPageContent.h"
#include "model/ui/cartWidgetContent.h"
#include "model/ui/orderPanelContent.h"
#include "model/ui/productPageContent.h"
#include "model/ui/receiptPageContent.h"
#include "model/ui/reviewContent.h"
#include "model/ui/wishPageContent.h"

#include <string>
#include <vector>

class ProductService;

class UiService {
    ProductService* productService{nullptr};

public:
    UiService() = default;

    void setProductService(ProductService* productService);

    int pageMaxIndex(int totalCount, int pageSize) const;

    ProductGridPageContent makeProductGridPageContent(const Products& products, int currentPage, int maxPage) const;
    ProductDetailContent makeProductDetailContent(const Product& product, bool wished) const;
    ProductFormContent makeProductFormContent(const Product& product) const;
    OrderPanelContent makeOrderPanelContent(const Order& order, int payment) const;
    CartWidgetContent makeCartWidgetContent(const Cart& cart) const;
    CartPageContent makeCartPageContent(const Cart& cart, int currentPage, int pageSize) const;
    ReceiptPageContent makeReceiptPageContent(const Receipts& receipts, int currentPage, int pageSize) const;
    WishPageContent makeWishPageContent(const Products& wishs, int currentPage, int pageSize) const;
    ReviewContent makeReviewContent(const Reviews& reviews, const std::vector<int>& manageableReviewIds, bool canWrite) const;

    std::string getReceiptItemSummary(const Receipt& receipt) const;
    std::string getReviewSummary(const Reviews& reviews) const;
};
