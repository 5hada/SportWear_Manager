#pragma once

#include <string>
#include <optional>
#include <vector>

#include "model/actions.h"
#include "model/product/cart.h"
#include "model/product/order.h"
#include "model/product/receipt.h"
#include "model/product/product.h"
#include "model/product/category.h"
#include "model/user/userInfo.h"
#include "model/review.h"
#include "model/ui/cartPageContent.h"
#include "model/ui/orderPanelContent.h"
#include "model/ui/productPageContent.h"
#include "model/ui/receiptPageContent.h"
#include "model/ui/reviewContent.h"
#include "model/ui/wishPageContent.h"

using std::string;
using std::optional;
using std::nullopt;

class ServiceProvider;

class EventHandler {
    ServiceProvider& service;
    int wishPageIndex{0};
    int cartPageIndex{0};
    int receiptPageIndex{0};

    int userId();
    bool hasPurchasedProduct(int productId);
    int pageMaxIndex(int totalCount, int pageSize) const;
    void movePageIndex(int& pageIndex, int delta, int maxPageIndex);
public:
    EventHandler(ServiceProvider& service): service(service) {}

    int getItemsPerPage() const {return 50;}

    UserInfo getUser();
    bool setUser(UserAction action, optional<string> name = nullopt, optional<string> password = nullopt);


    bool setProducts(int index = -1, optional<string> keyword = nullopt, optional<Category> category = nullopt);
    ProductGridPageContent getProductsContents();

    bool setProduct(int productId);
    Product getProduct();
    bool canManageProducts();

    bool setOrder(int productId = -1);
    Order getOrder();
    OrderPanelContent getOrderPanelContent(int usedPoint = 0);
    int getOrderTotalPrice();
    int getOrderAvailablePoints();
    int getOrderMaxUsablePoint();
    int getOrderPayment(int usedPoint);
    bool confirmOrder(int usedPoint = 0);
    
    bool refund(int receiptId);

    Cart getCart();
    CartPageContent getCartPageContent(int pageSize = 8);
    CartPageContent moveCartPage(int delta, int pageSize = 8);
    bool handleCart(
        CartAction action,
        int productId = -1,
        int count = 0,
        std::optional<bool> isSelected = std::nullopt
    );


    Receipts getReceipts();
    ReceiptPageContent getReceiptPageContent(int pageSize = 8);
    ReceiptPageContent moveReceiptPage(int delta, int pageSize = 8);
    
    Products getWishs();
    WishPageContent getWishPageContent(int pageSize = 8);
    WishPageContent moveWishPage(int delta, int pageSize = 8);
    bool isWished(int productId);
    bool setWish(int productId, bool isWished = true);

    int getUserId();
    bool canWriteReview(int productId);
    std::vector<int> getManageableReviewIds(int productId);
    string getReviewSummary(int productId);
    Reviews getReviews(int productId);
    ProductReviewContent getProductReviewContent(int productId);
    bool saveReview(int reviewId, int productId, int rating, const string& comment);
    bool deleteReview(int reviewId);
    bool setReview(Review review);

    bool updateProduct(Product product);
    bool updateProductForm(int productId, const string& name, Category category, int price, int stock, const string& detail);
    string getReceiptItemSummary(const Receipt& receipt);
};











