#pragma once

#include <string>
#include <optional>
#include <vector>

#include "model/actions.h"
#include "model/product/cart.h"
#include "model/product/receipt.h"
#include "model/product/product.h"
#include "model/product/category.h"
#include "model/ui/userInfo.h"
#include "model/review.h"
#include "model/ui/cartPageContent.h"
#include "model/ui/cartWidgetContent.h"
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

    int userId();
    bool hasPurchasedProduct(int productId);
    bool canWriteReview(int productId);
    std::vector<int> getManageableReviewIds(int productId);
    Reviews getReviews(int productId);
    Cart getCart();
    bool updateProduct(Product product);
public:
    EventHandler(ServiceProvider& service): service(service) {}

    int getItemsPerPage() const {return 50;}

    UserInfo getUser();
    bool setUser(UserAction action, optional<string> name = nullopt, optional<string> password = nullopt);


    bool setProducts(int index = -1, optional<string> keyword = nullopt, optional<Category> category = nullopt);
    ProductGridPageContent getProductsContents();

    bool setProduct(int productId);
    int getCurrentProductId();
    ProductDetailContent getProductDetailContent();
    ProductFormContent getProductFormContent();
    bool canManageProducts();
    bool canUseCart();

    bool setOrder(int productId = -1);
    OrderPanelContent getOrderPanelContent(int usedPoint = 0);
    int getOrderPayment(int usedPoint);
    bool confirmOrder(int usedPoint = 0);
    
    bool refund(int receiptId);

    CartWidgetContent getCartWidgetContent();
    CartPageContent getCartPageContent(int pageSize = 8);
    CartPageContent moveCartPage(int delta, int pageSize = 8);
    bool handleCart(
        CartAction action,
        int productId = -1,
        int count = 0,
        std::optional<bool> isSelected = std::nullopt
    );


    ReceiptPageContent getReceiptPageContent(int pageSize = 8);
    ReceiptPageContent moveReceiptPage(int delta, int pageSize = 8);
    
    WishPageContent getWishPageContent(int pageSize = 8);
    WishPageContent moveWishPage(int delta, int pageSize = 8);
    bool isWished(int productId);
    bool setWish(int productId, bool isWished = true);

    ReviewContent getReviewContent(int productId);
    bool saveReview(int reviewId, int productId, int rating, const string& comment);
    bool deleteReview(int reviewId);

    bool updateProductForm(int productId, const string& name, Category category, int price, int stock, const string& detail);
};






