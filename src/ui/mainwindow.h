#pragma once

#include <ElaWindow.h>

class QStackedWidget;
class ElaPushButton;

class AdminController;
class AuthController;
class CartController;
class OrderController;
class ProductController;

class ProductDetailPage;
class ProductGridPage;
class OrderPanel;
class ReceiptPage;
class CartPage;
class CartWidget;
class WishPage;
class Dialog;

class MainWindow : public ElaWindow{
    Q_OBJECT

    AdminController& admin;
    AuthController& auth;
    CartController& cart;
    OrderController& order;
    ProductController& product;

    QStackedWidget* productPages{nullptr};
    ProductGridPage* productGridPage{nullptr};
    ProductDetailPage* productDetailPage{nullptr};
    OrderPanel* orderPanel{nullptr};
    ReceiptPage* receiptPage{nullptr};
    CartWidget* cartWidget{nullptr};
    CartPage* cartPage{nullptr};
    WishPage* wishPage{nullptr};
    Dialog* dialog{nullptr};
    ElaPushButton* cartButton{nullptr};

    QString categoriesKey;
    QString settingsKey;
    QString profileKey;
    QString loginKey;
    QString logoutKey;
    
    void initWindow();
    void initContent();
    void initConnect();

    void connectPages();

    void showProductPage();
    void showDetailPage(int productId);
    void showOrderPanel();
    void showReceiptPage();
    void showCartWidget();
    void showCartPage();
    void showWishPage();

    void showLoginPanel();
    void showLogoutPanel();
    void showSignupPanel();

    void adjustCartButton();

public:
    MainWindow(
        AdminController& admin,
        AuthController& auth,
        CartController& cart,
        OrderController& order,
        ProductController& product
    );
};
