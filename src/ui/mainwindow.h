#pragma once


#include "app/appContext.h"

#include <ElaWindow.h>
#include <qstackedwidget.h>

class LoginPage;
class ProductDetailPage;
class ProductGridPage;
class ReceiptPage;
class WishPage;
class CartWidget;
class ProfilePanel;
class AlertDialog;

class MainWindow : public ElaWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void initWindow();
    void initContent();

    void connectNavigations();
    void connectPages();


    void refreshProducts();
    void refreshWishProducts();
    void refreshCart();
    bool requireLogin();

    void initAlertDialog();

    AppContext app;
    LoginPage* loginPage{nullptr};
    ProductGridPage* productGridPage{nullptr};
    ProductDetailPage* productDetailPage{nullptr};
    QStackedWidget* productPages{nullptr};
    ReceiptPage* receiptPage{nullptr};
    WishPage* wishPage{nullptr};
    CartWidget* cartWidget{nullptr};
    ProfilePanel* profilePanel{nullptr};
    AlertDialog* alertDialog{nullptr};

    QString settingsKey;
    QString logoutKey;
    QString profileKey;
};
