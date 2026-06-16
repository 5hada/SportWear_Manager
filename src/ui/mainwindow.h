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
class Dialog;
class ElaPushButton;

class MainWindow : public ElaWindow{
    Q_OBJECT

    AppContext app;
    LoginPage* loginPage{nullptr};
    ProductGridPage* productGridPage{nullptr};
    ProductDetailPage* productDetailPage{nullptr};
    QStackedWidget* productPages{nullptr};
    ReceiptPage* receiptPage{nullptr};
    WishPage* wishPage{nullptr};
    CartWidget* cartWidget{nullptr};
    ProfilePanel* profilePanel{nullptr};
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

    void refreshProducts();
    void refreshWishProducts();
    void refreshCart();
    
    bool isLoggedIn();

    int userId();
    std::string userName();
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
};
