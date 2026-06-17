#include <string>

#include "model/product/cart.h"
#include "model/product/cartAction.h"
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

    string getName();
    int getPoint();

    Cart getCart();
    bool handleCart(CartAction action, int productId, int count);

    Receipts getReceipts();
    bool refund(int receiptId);

    Products getAll();
    Products getCategory(Category category);
    Products getWishAll();
    Product getProduct(int productId);

    bool setWish(int productId);
};