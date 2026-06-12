#pragma once

#include "app/appContext.h"

#include <ElaWindow.h>

class LoginPage;
class ProductDetailPage;
class ProductGridPage;
class ReceiptPage;
class WishPage;
class CartWidget;
class ProfilePanel;

class MainWindow : public ElaWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void initWindow();
    void initContent();
    void connectPages();
    void refreshProducts();
    void refreshWishProducts();
    void refreshCart();
    bool requireLogin();

    AppContext app;
    LoginPage* loginPage{nullptr};
    ProductGridPage* productGridPage{nullptr};
    ProductDetailPage* productDetailPage{nullptr};
    ReceiptPage* receiptPage{nullptr};
    WishPage* wishPage{nullptr};
    CartWidget* cartWidget{nullptr};
    ProfilePanel* profilePanel{nullptr};

    QString settingsKey;
    QString logoutKey;
    QString profileKey;
};
