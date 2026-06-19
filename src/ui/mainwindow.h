#pragma once

#include "model/product/category.h"
#include <ElaWindow.h>
#include <QString>
#include <functional>
#include <optional>
#include <string>

class Order;

class QStackedWidget;
class ElaPushButton;
class QWidget;

class EventHandler;
// class ElaProgressRing;

class ProductGridPage;
class ProductDetailPage;
class ProfilePanel;
class OrderPanel;
class ReceiptPage;
class CartPage;
class CartWidget;
class WishPage;
class Dialog;
class SettingPanel;

class MainWindow : public ElaWindow{
    Q_OBJECT

    EventHandler& event;

    // ElaProgressRing* progressRing{nullptr};

    QStackedWidget* productPages{nullptr};
    ProductGridPage* productGridPage{nullptr};
    ProductDetailPage* productDetailPage{nullptr};
    ReceiptPage* receiptPage{nullptr};
    CartPage* cartPage{nullptr};
    WishPage* wishPage{nullptr};
    
    OrderPanel* orderPanel{nullptr};
    SettingPanel* settingPanel{nullptr};
    ProfilePanel* profilePanel{nullptr};
    CartWidget* cartWidget{nullptr};
    Dialog* dialog{nullptr};

    ElaPushButton* cartButton{nullptr};

    QString prevNodeKey;
    QString homeKey;
    QString productsKey;
    QString settingKey;
    QString profileKey;
    Category currentCategory{Category::Unknown};
    std::optional<std::string> currentKeyword{std::nullopt};
    
    void initWindow();

    // void showLoading();
    // void hideLoading();

    void initContent();
    void initConnect();

    void connectNavigation();
    void connectPageRequests();

    void connectProductsPage();
    void connectDetailPage();
    void connectReceiptPage();
    void connectCartPage();
    void connectWishPage();

    void connectOrderPanel();
    void connectSettingPanel();
    void connectProfilePanel();
    // void connectDialog();
    void connectCartWidget();

    void showProductPage();
    void showDetailPage();
    void showReceiptPage();
    void showCartPage();
    void showWishPage();

    void showOrderPanel();
    void showSettingPanel();

    void showProfilePanel();
    void updateUserInfo();
    void refreshProductPage(int pageIndex = 0);
    void movePanelToWindowCenter(QWidget* panel);

    void openCartWidget();
    void closeCartWidget();
    void adjustCartButton();

    void handleResult(bool result, const std::function<void()>& callback = {});
public:
    MainWindow(EventHandler& event);
};
