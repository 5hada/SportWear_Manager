#include "mainwindow.h"

#include "ElaPushButton.h"
#include "messageBar.h"

#include "controller/adminController.h"
#include "controller/authController.h"
#include "controller/cartController.h"
#include "controller/orderController.h"
#include "controller/productController.h"

#include "model/product/cartAction.h"
#include "model/product/product.h"
#include "page/productDetailPage.h"
#include "page/productGridPage.h"
#include "page/orderPanel.h"
#include "page/receiptPage.h"
#include "page/wishPage.h"
#include "page/cart/cartWidget.h"
#include "page/cart//cartPage.h"

#include "dialog.h"
#include "messageBar.h"
#include "ui/messageBar.h"

#include <ElaDef.h>
#include <ElaIcon.h>
#include <ElaText.h>
#include <QMessageBox>
#include <qobject.h>
#include <qpoint.h>
#include <qstackedwidget.h>

MainWindow::MainWindow(
    AdminController& admin,
    AuthController& auth,
    CartController& cart,
    OrderController& order,
    ProductController& product
):
    admin(admin), auth(auth), cart(cart), order(order), product(product) {
    initWindow();
    initContent();
    initConnect();
}

void MainWindow::initWindow() {
    setWindowTitle("SportWear Manager");
    resize(1200, 760);
    moveToCenter();
    setFocusPolicy(Qt::StrongFocus);
    setUserInfoCardTitle(QString::fromStdString(auth.getName()));
    setUserInfoCardSubTitle("Not signed in");

    auto* landingText = new ElaText("SportWear Manager", this);
    landingText->setTextPixelSize(32);
    landingText->setAlignment(Qt::AlignCenter);
    addCentralWidget(landingText);
}

void MainWindow::initContent() {
    productPages = new QStackedWidget(this);
    productGridPage = new ProductGridPage(this);
    productDetailPage = new ProductDetailPage(this);
    productPages->addWidget(productGridPage);
    productPages->addWidget(productDetailPage);
    productPages->setCurrentWidget(productGridPage);

    orderPanel = new OrderPanel(this);
    orderPanel->hide();
    receiptPage = new ReceiptPage(this);
    cartWidget = new CartWidget(this);\
    cartWidget->hide();
    cartPage = new CartPage(this);
    wishPage = new WishPage(this);

    dialog = new Dialog(this);
    dialog->hide();

    cartButton  = new ElaPushButton{this};
    cartButton->setFixedWidth(50);
    adjustCartButton();

    addPageNode("Home", productPages, ElaIconType::House);

    addPageNode("Products", productPages, ElaIconType::Shirt);
    addExpanderNode("Categories", categoriesKey, ElaIconType::GridRound2);
    for (auto& category: Categories){
        addPageNode(QString::fromStdString(categoryToString(category)), productPages, categoriesKey, ElaIconType::Shirt);
    }
    addPageNode("Wish", wishPage, ElaIconType::Heart);
    addPageNode("Cart", cartPage, ElaIconType::CartShopping);
    addPageNode("Orders", receiptPage, ElaIconType::ClockRotateLeft);

    addFooterNode("Settings", settingsKey, 0,ElaIconType::GearComplex);
    addFooterNode("Login", loginKey, 0,ElaIconType::User);
    addFooterNode("Logout", logoutKey, 0,ElaIconType::ArrowRightFromBracket);
    
    addDockWidget(Qt::RightDockWidgetArea, cartWidget);


    showProductPage();
}

void MainWindow::initConnect() {
    connect(this, &MainWindow::userInfoCardClicked, this, [=]() {
        showProductPage();
        return;
    });

    connect(this, &ElaWindow::navigationNodeClicked, this,
            [this](ElaNavigationType::NavigationNodeType, const QString& nodeKey) {
                if (nodeKey == productPages->property("ElaPageKey").toString()) {
                    showProductPage();
                }
                if (nodeKey == wishPage->property("ElaPageKey").toString()) {
                    showWishPage();
                }
                if (nodeKey == cartPage->property("ElaPageKey").toString()) {
                    showCartPage();
                }
                if (nodeKey == receiptPage->property("ElaPageKey").toString()) {
                    showReceiptPage();
                }
                if (nodeKey == settingsKey) {
                    return;
                }
                if (nodeKey == loginKey) {
                    dialog->moveToCenter();
                    dialog->setLoginForm();
                    dialog->show();
                    return;
                }
                if (nodeKey == logoutKey) {
                    dialog->moveToCenter();
                    dialog->setLogoutAlert();
                    dialog->show();
                    return;
                }
            }
        );
    connect(dialog, &Dialog::rightClicked, this, [=]() {
        auth.logout();
        setUserInfoCardTitle("Guest");
        setUserInfoCardSubTitle("Not signed in");
        MessageBar::Logout(this);
    });

    connectPages();
}

void MainWindow::connectPages() {
    connect(loginPage, &LoginPage::loginRequested, this, [this](const QString& name, const QString& password) {
        const auto success = auth.login(name.toStdString(), password.toStdString());
        if (!success) {
            MessageBar::Fail(this);
        }

        setUserInfoCardTitle(QString::fromStdString(auth.getName()));
        setUserInfoCardSubTitle(QString("Point %1\nSigned in.").arg(auth.getPoint()));
        showProductPage();
        navigation(productGridPage->property("ElaPageKey").toString());
    });

    connect(productGridPage, &ProductGridPage::productSelected, this, [this](const Product& product) {
        productDetailPage->setProduct(product);
        productPages->setCurrentWidget(productDetailPage);
    });

    connect(productDetailPage, &ProductDetailPage::cartRequest, this, [this](int productId) {
        if (!cart.handleCart(CartAction::Add, productId, 1)) {
            MessageBar::Fail(this);
            return;
        }
        cartWidget->show();
    });

    connect(productDetailPage, &ProductDetailPage::wishRequest, this, [this](int productId) {
        product.setWish(productId);
    });
}

void MainWindow::showProductPage() {
    productGridPage->setProducts(product.getAll());
    navigation(productGridPage->property("ElapageKey").toString());
}

void MainWindow::showDetailPage(int productId) {
   productDetailPage->setProduct(product.getProduct(productId));
//    navigation(detailPage)
}

void MainWindow::showCartPage() {
    
}

void MainWindow::showWishPage() {
    wishPage->setWishProducts(product.getWishAll());
    navigation(wishPage->property("ElaPageKey").toString());
}

void MainWindow::showOrderPanel() {
    
}

void MainWindow::showReceiptPage() {
    receiptPage->setReceipts(order.getReceipts());
    navigation(receiptPage->property("ElaPageKey").toString());
}

void MainWindow::adjustCartButton() {
    cartButton->move(
        this->width() - cartButton->width() - 20,
        this->height() - cartButton->height() - 10
    );
}