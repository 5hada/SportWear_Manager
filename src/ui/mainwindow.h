#pragma once

#include "model/product/category.h"
#include <ElaWindow.h>
#include <map>

class QStackedWidget;
class ElaPushButton;

class EventHandler;
class Order;

class ProductDetailPage;
class ProductGridPage;
class ProfilePanel;
class OrderPanel;
class ReceiptPage;
class CartPage;
class CartWidget;
class WishPage;
class Dialog;

class MainWindow : public ElaWindow{
    Q_OBJECT

    EventHandler& event;

    QStackedWidget* productPages{nullptr};
    ProductGridPage* productGridPage{nullptr};
    std::map<Category,ProductGridPage*> productCategoryPages;
    ProductDetailPage* productDetailPage{nullptr};
    ProfilePanel* profilePanel{nullptr};
    OrderPanel* orderPanel{nullptr};
    ReceiptPage* receiptPage{nullptr};
    CartWidget* cartWidget{nullptr};
    CartPage* cartPage{nullptr};
    WishPage* wishPage{nullptr};
    Dialog* dialog{nullptr};
    ElaPushButton* cartButton{nullptr};
    bool navigatingToProductDetail{false};
    QString detailReturnNodeKey;

    QString categoriesKey;
    QString settingsKey;
    QString profileKey;
    
    void initWindow();
    void initContent();
    void initConnect();

    void connectNavigation();
    void connectPages();

    void updateUserInfo();

    void showProductPage();
    void showProductCategoryPage(Category category);
    void showDetailPage(int productId, const QString& returnNodeKey = QString());
    void showOrderPanel(const Order& order);
    void showReceiptPage();
    void showCartWidget();
    void showCartPage();
    void showWishPage();

    void showUserPanel();
    void showLoginPanel();
    void showLogoutPanel();
    void showSignupPanel();

    void adjustCartButton();
public:
    MainWindow(
        EventHandler& event
    );
};
