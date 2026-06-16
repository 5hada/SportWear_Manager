#include "mainwindow.h"

#include "ElaPushButton.h"
#include "messageBar.h"


#include "model/product/cartAction.h"
#include "model/product/category.h"
#include "model/product/product.h"
#include "page/loginPage.h"
#include "page/productDetailPage.h"
#include "page/productGridPage.h"
#include "page/receiptPage.h"
#include "page/wishPage.h"
#include "page/cart/cartWidget.h"
#include "page/profilePanel.h"
#include "dialog.h"

#include <ElaDef.h>
#include <ElaIcon.h>
#include <ElaText.h>
#include <QMessageBox>
#include <qstackedwidget.h>

MainWindow::MainWindow(QWidget* parent): ElaWindow(parent) {
    initWindow();
    initContent();
    initConnect();
}

MainWindow::~MainWindow() = default;

void MainWindow::initWindow() {
    setWindowTitle("SportWear Manager");
    resize(1200, 760);
    setFocusPolicy(Qt::StrongFocus);
    setUserInfoCardTitle(QString::fromStdString(userName()));
    setUserInfoCardSubTitle(app.repositories.isDatabaseReady() ?
        "Not signed in" :
        "Database unavailable"
    );

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


    productPages = new QStackedWidget(this);
    productGridPage = new ProductGridPage(this);
    productDetailPage = new ProductDetailPage(this);
    productPages->addWidget(productGridPage);
    productPages->addWidget(productDetailPage);
    productPages->setCurrentWidget(productGridPage);

    dialog = new Dialog(this);
    cartButton  = new ElaPushButton{this};


    addPageNode("Home", productPages, ElaIconType::House);

    addPageNode("Products", productPages, ElaIconType::Shirt);
    addExpanderNode("Categories", categoriesKey, ElaIconType::GridRound2);
    for (auto& category: Categories){
        addPageNode(QString::fromStdString(categoryToString(category)), productPages, categoriesKey, ElaIconType::Shirt);
    }
    addPageNode("Wish", wishPage, ElaIconType::Heart);
    addPageNode("Cart", wishPage, ElaIconType::CartShopping);
    addPageNode("Orders", receiptPage, ElaIconType::ClockRotateLeft);

    addFooterNode("Settings", settingsKey, 0,ElaIconType::GearComplex);
    addFooterNode("Login", loginKey, 0,ElaIconType::User);
    addFooterNode("Logout", logoutKey, 0,ElaIconType::ArrowRightFromBracket);

    dialog->hide();
    profilePanel->hide();


    addDockWidget(Qt::RightDockWidgetArea, cartWidget);
    cartWidget->hide();


    refreshProducts();
    refreshWishProducts();
    refreshCart();

    navigation(productGridPage->property("ElaPageKey").toString());
}

void MainWindow::initConnect() {
    connect(this, &MainWindow::userInfoCardClicked, this, [=]() {
        this->navigation(productGridPage->property("ElaPageKey").toString());
        refreshProducts();
        return;
    });

    connect(this, &ElaWindow::navigationNodeClicked, this,
            [this](ElaNavigationType::NavigationNodeType, const QString& nodeKey) {
                if (nodeKey == settingsKey) {
                    navigation(loginPage->property("ElaPageKey").toString());
                    return;
                }
                if (nodeKey == logoutKey) {
                    dialog->moveToCenter();
                    dialog->setLogoutAlert();
                    dialog->show();
                    return;
                }
                if (nodeKey == productGridPage->property("ElaPageKey").toString()) {
                    refreshProducts();
                }
                if (nodeKey == wishPage->property("ElaPageKey").toString()) {
                    refreshWishProducts();
                }
            }
        );
    connect(dialog, &Dialog::rightClicked, this, [=]() {
        app.services.account.logout();
        setUserInfoCardTitle("Guest");
        setUserInfoCardSubTitle("Not signed in");
        loginPage->setStatus("Signed out.");
        refreshCart();             
        MessageBar::Logout(this);
    });

    connectPages();
}

void MainWindow::connectPages() {
    connect(loginPage, &LoginPage::loginRequested, this, [this](const QString& name, const QString& password) {
        const auto success = app.services.account.login(name.toStdString(), password.toStdString());
        if (!success) {
            loginPage->setStatus("Login failed.");
            return;
        }

        setUserInfoCardTitle(QString::fromStdString(userName()));
        auto point = app.services.point.getPoint(userId());
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
        if (!isLoggedIn()) {return;}
        if (!app.services.cart.handleCart(CartAction::Add,userId(), productId, 1)) {
            QMessageBox::warning(this, "Cart", "Failed to add product to cart.");
            return;
        }
        refreshCart();
        cartWidget->show();
    });

    connect(productDetailPage, &ProductDetailPage::addWishRequested, this, [this](int productId) {
        if (!isLoggedIn()) {return;}
        app.services.wish.add(userId(), productId);
        refreshWishProducts();
        navigation(wishPage->property("ElaPageKey").toString());
    });
}


void MainWindow::refreshProducts() {
    productGridPage->setProducts(app.services.product.getAll());
}

void MainWindow::refreshWishProducts() {
    std::vector<Product> products;
    int id = userId();
    if (id != 0) {
        for (const int productId : app.repositories.wish.findByUser(id)) {
            auto product = app.services.product.getOptById(productId);
            if (product.has_value()) {
                products.push_back(*product);
            }
        }
    }
    wishPage->setWishProducts(std::move(products));
}

void MainWindow::refreshCart() {
    int id = userId();
    cartWidget->setCart(id == 0 ? Cart() : app.services.cart.getCart(id));
}


bool MainWindow::isLoggedIn() {
    return app.services.account.loggedIn();
}

int MainWindow::userId() {
    return app.services.account.getUserId();
}

std::string MainWindow::userName() {
    return app.services.account.getUserName();
}