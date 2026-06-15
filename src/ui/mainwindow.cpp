#include "mainwindow.h"



#include "model/product/cartAction.h"
#include "model/product/product.h"
#include "page/loginPage.h"
#include "page/productDetailPage.h"
#include "page/productGridPage.h"
#include "page/receiptPage.h"
#include "page/wishPage.h"
#include "page/cart/cartWidget.h"
#include "page/profilePanel.h"
#include "page/alertDialog.h"

#include <ElaDef.h>
#include <ElaIcon.h>
#include <ElaText.h>
#include <QMessageBox>
#include <qstackedwidget.h>
#include <ElaMessageBar.h>

MainWindow::MainWindow(QWidget* parent): ElaWindow(parent) {
    initWindow();
    initContent();
}

MainWindow::~MainWindow() = default;

void MainWindow::initWindow() {
    setWindowTitle("SportWear Manager");
    resize(1200, 760);
    setFocusPolicy(Qt::StrongFocus);
    setUserInfoCardTitle("Guest");
    setUserInfoCardSubTitle(app.repositories.isDatabaseReady() ? "Not signed in" : "Database unavailable");

    auto* landingText = new ElaText("SportWear Manager", this);
    landingText->setTextPixelSize(32);
    landingText->setAlignment(Qt::AlignCenter);
    addCentralWidget(landingText);
}

void MainWindow::initContent() {
    loginPage = new LoginPage(this);
    profilePanel = new ProfilePanel(this);
    receiptPage = new ReceiptPage(this);
    wishPage = new WishPage(this);
    cartWidget = new CartWidget(this);

    // ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", "", 3);

    initAlertDialog();

    productPages = new QStackedWidget(this);
    productGridPage = new ProductGridPage(this);
    productDetailPage = new ProductDetailPage(this);
    productPages->addWidget(productGridPage);
    productPages->addWidget(productDetailPage);
    productPages->setCurrentWidget(productGridPage);

    addPageNode("Products", productPages, ElaIconType::Cards);
    addPageNode("Wish List", wishPage, ElaIconType::Heart);
    addPageNode("Login", loginPage, ElaIconType::User);
    addPageNode("History", receiptPage, ElaIconType::ClockRotateLeft);

    addFooterNode("Settings", settingsKey, 0, ElaIconType::GearComplex);
    addFooterNode("Logout", logoutKey, 0, ElaIconType::ArrowRightFromBracket);

    alertDialog->hide();
    profilePanel->hide();
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if (logoutKey == nodeKey) {
            alertDialog->moveToCenter();
            alertDialog->show();
        }
    });

    addDockWidget(Qt::RightDockWidgetArea, cartWidget);
    cartWidget->hide();

    connect(this, &MainWindow::userInfoCardClicked, this, [=]() {
        this->navigation(loginPage->property("ElaPageKey").toString());
    });

    connect(this, &ElaWindow::navigationNodeClicked, this,
            [this](ElaNavigationType::NavigationNodeType, const QString& nodeKey) {
                if (nodeKey == settingsKey) {
                    navigation(loginPage->property("ElaPageKey").toString());
                    return;
                }
                if (nodeKey == productGridPage->property("ElaPageKey").toString()) {
                    refreshProducts();
                }
                if (nodeKey == wishPage->property("ElaPageKey").toString()) {
                    refreshWishProducts();
                }
            });

    connectPages();
    refreshProducts();
    refreshCart();
    navigation(productGridPage->property("ElaPageKey").toString());
}

void MainWindow::initAlertDialog(){
    alertDialog = new AlertDialog(this);
    connect(alertDialog, &AlertDialog::exitClicked, this, [=]() {
        app.services.account.logout();
        setUserInfoCardTitle("Guest");
        setUserInfoCardSubTitle("Not signed in");
        loginPage->setStatus("Signed out.");
        refreshCart();             
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "Signed out", "", 3000, this);
    });
}

void MainWindow::connectPages()
{
    connect(loginPage, &LoginPage::loginRequested, this, [this](const QString& name, const QString& password) {
        const auto success = app.services.account.login(name.toStdString(), password.toStdString());
        if (!success) {
            loginPage->setStatus("Login failed.");
            return;
        }

        setUserInfoCardTitle(QString::fromStdString(app.services.account.getUserName()));
        auto point = app.services.point.getPoint(app.services.account.getUserId());
        setUserInfoCardSubTitle(QString("Point %1").arg(point));
        loginPage->setStatus("Signed in.");
        refreshProducts();
        refreshWishProducts();
        refreshCart();
        navigation(productGridPage->property("ElaPageKey").toString());
    });

    connect(productGridPage, &ProductGridPage::productSelected, this, [this](const Product& product) {
        productDetailPage->setProduct(product);
        productPages->setCurrentWidget(productDetailPage);
    });

    connect(productDetailPage, &ProductDetailPage::addCartRequested, this, [this](int productId) {
        if (!requireLogin()) {
            return;
        }
        if (!app.services.cart.handleCart(CartAction::Add,app.services.account.getUserId(), productId, 1)) {
            QMessageBox::warning(this, "Cart", "Failed to add product to cart.");
            return;
        }
        refreshCart();
        cartWidget->show();
    });

    connect(productDetailPage, &ProductDetailPage::addWishRequested, this, [this](int productId) {
        if (!requireLogin()) {
            return;
        }
        app.services.wish.add(app.services.account.getUserId(), productId);
        refreshWishProducts();
        navigation(wishPage->property("ElaPageKey").toString());
    });
}

void MainWindow::refreshProducts() {
    productGridPage->setProducts(app.services.product.listProducts());
}

void MainWindow::refreshWishProducts() {
    std::vector<Product> products;
    if (app.services.account.getUserId() != 0) {
        for (const int productId : app.repositories.wish.findByUser(app.services.account.getUserId())) {
            auto product = app.services.product.getProduct(productId);
            if (product.has_value()) {
                products.push_back(*product);
            }
        }
    }
    wishPage->setWishProducts(std::move(products));
}

void MainWindow::refreshCart() {
    cartWidget->setCart(app.services.account.getUserId() == 0 ? Cart() : app.services.cart.getCart(app.services.account.getUserId()));
}

bool MainWindow::requireLogin() {
    if (app.services.account.loggedIn()) {
        return true;
    }

    loginPage->setStatus("Login required.");
    navigation(loginPage->property("ElaPageKey").toString());
    return false;
}
