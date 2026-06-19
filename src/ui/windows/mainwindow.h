#pragma once

#include "model/product/category.h"
#include <ElaWindow.h>
#include <QString>
#include <functional>

class Order;

class QStackedWidget;
class ElaPushButton;
class QWidget;

class EventHandler;

class ProductGridPage;
class ProductDetailPage;
class ProductEditPage;
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

    QStackedWidget* productPages{nullptr};
    ProductGridPage* productGridPage{nullptr};
    ProductDetailPage* productDetailPage{nullptr};
    ProductEditPage* productEditPage{nullptr};
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
    bool productEditReturnToDetail{false};
    
    void initWindow();

    void initContent();
    void initConnect();

    void connectNavigation();
    void connectPageRequests();

    void connectProductsPage();
    void connectDetailPage();
    void connectEditPage();
    void connectReceiptPage();
    void connectCartPage();
    void connectWishPage();

    void connectOrderPanel();
    void connectSettingPanel();
    void connectProfilePanel();
    void connectCartWidget();

    void showProductPage();
    void showDetailPage();
    void showProductAddPage();
    void showProductEditPage();
    void showReceiptPage();
    void showCartPage();
    void showWishPage();

    void showOrderPanel();
    void showSettingPanel();

    void showProfilePanel();
    void updateUserInfo();
    void refreshProductPage(int pageIndex = 0);
    void refreshProductDetailReviews(int productId);
    void refreshReceiptPageContents();
    void movePanelToWindowCenter(QWidget* panel);
    void updateAdminControls();

    void openCartWidget();
    void closeCartWidget();
    void adjustCartButton();

    void handleResult(bool result, const std::function<void()>& callback = {});
public:
    MainWindow(EventHandler& event);
};
