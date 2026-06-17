#include <string>
#include <optional>

#include "model/product/cart.h"
#include "model/product/cartAction.h"
#include "model/product/order.h"
#include "model/product/receipt.h"
#include "model/product/product.h"
#include "model/product/category.h"

using std::string;

class ServiceProvider;

class EventHandler {
    ServiceProvider& service;

    int userId();
public:
    EventHandler(ServiceProvider& service): service(service) {}


    bool signup(string name, string password);
    bool login(string name, string password);
    bool logout();
    bool isLoggedIn();

    string getName();
    int getPoint();



    Cart getCart();
    bool handleCart(
        CartAction action,
        int productId = 0,
        int count = 0,
        std::optional<bool> isSelected = std::nullopt
    );




    bool makeOrder(int productId = -1);
    std::tuple<Order&,int>  getOrder(int productId = -1);
    bool confirmOrder(int usedPoint = 0);

    Receipts getReceipts();
    bool refund(int receiptId);




    Products getAll();
    Products getCategory(Category category);
    Products getWishAll();
    Product getProduct(int productId);

    bool setWish(int productId);
};
