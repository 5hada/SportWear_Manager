#include <string>
#include <optional>

#include "model/actions.h"
#include "model/product/cart.h"
#include "model/product/order.h"
#include "model/product/receipt.h"
#include "model/product/product.h"
#include "model/product/category.h"
#include "model/user/userInfo.h"
#include "model/review.h"

using std::string;
using std::optional;
using std::nullopt;

class ServiceProvider;

class EventHandler {
    ServiceProvider& service;

    int userId();
public:
    EventHandler(ServiceProvider& service): service(service) {}

    int getItemsPerPage() const {return 50;}

    UserInfo getUser();
    bool setUser(UserAction action, optional<string> name = nullopt, optional<string> password = nullopt);


    bool setProducts(int index = -1, optional<string> keyword = nullopt, optional<Category> category = nullopt);
    std::tuple<Products, int, int> getProductsContents();

    bool setProduct(int productId);
    Product getProduct();

    bool setOrder(int productId = -1);
    Order getOrder();
    bool confirmOrder(int usedPoint = 0);
    
    bool refund(int receiptId);

    Cart getCart();
    bool handleCart(
        CartAction action,
        int productId = -1,
        int count = 0,
        std::optional<bool> isSelected = std::nullopt
    );


    Receipts getReceipts();
    
    Products getWishs();
    bool isWished(int productId);
    bool setWish(int productId, bool isWished = true);

    Reviews getReviews(int productId);
    bool setReview(Review review);

    bool updateProduct(Product product);
};











