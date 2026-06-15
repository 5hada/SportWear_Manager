#include "mainwindow.h"

#include "page/loginPage.h"
#include "page/productDetailPage.h"
#include "page/productGridPage.h"
#include "page/receiptPage.h"
#include "page/wishPage.h"
#include "page/cart/cartWidget.h"
#include "page/profilePanel.h"

#include <ElaDef.h>
#include <ElaIcon.h>
#include <ElaText.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : ElaWindow(parent)
{
    initWindow();
    initContent();
}

MainWindow::~MainWindow() = default;

void MainWindow::initWindow()
{
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

void MainWindow::initContent()
{
    loginPage = new LoginPage(this);
    productGridPage = new ProductGridPage(this);
    productDetailPage = new ProductDetailPage(this);
    receiptPage = new ReceiptPage(this);
    wishPage = new WishPage(this);
    cartWidget = new CartWidget(this);

    addPageNode("Products", productGridPage, ElaIconType::Cards);
    addPageNode("Product Detail", productDetailPage, ElaIconType::Table);
    addPageNode("Wish List", wishPage, ElaIconType::Heart);
    addPageNode("Login", loginPage, ElaIconType::User);
    addPageNode("History", receiptPage, ElaIconType::ClockRotateLeft);

    addFooterNode("Settings", settingsKey, 0, ElaIconType::GearComplex);
    addFooterNode("Profile", nullptr, profileKey, 0, ElaIconType::User);
    profilePanel = new ProfilePanel();

    profilePanel->hide();
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if (profileKey == nodeKey)
        {
            profilePanel->moveToCenter();
            profilePanel->show();
        }
    });
    addFooterNode("Logout", logoutKey, 0, ElaIconType::ArrowRightFromBracket);

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
                if (nodeKey == logoutKey) {
                    app.currentUserId = 0;
                    setUserInfoCardTitle("Guest");
                    setUserInfoCardSubTitle("Not signed in");
                    loginPage->setStatus("Signed out.");
                    refreshCart();
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

void MainWindow::connectPages()
{
    connect(loginPage, &LoginPage::loginRequested, this, [this](const QString& name, const QString& password) {
        const auto user = app.services.login.login(name.toStdString(), password.toStdString());
        if (!user.has_value()) {
            loginPage->setStatus("Login failed.");
            return;
        }

        app.currentUserId = user->getId();
        setUserInfoCardTitle(QString::fromStdString(user->getName()));
        setUserInfoCardSubTitle(QString("Point %1").arg(user->getPoint()));
        loginPage->setStatus("Signed in.");
        refreshProducts();
        refreshWishProducts();
        refreshCart();
        navigation(productGridPage->property("ElaPageKey").toString());
    });

    connect(productGridPage, &ProductGridPage::productSelected, this, [this](const Product& product) {
        productDetailPage->setProduct(product);
        navigation(productDetailPage->property("ElaPageKey").toString());
    });

    connect(productDetailPage, &ProductDetailPage::addCartRequested, this, [this](int productId) {
        if (!requireLogin()) {
            return;
        }
        if (!app.services.cart.addProduct(app.currentUserId, productId, 1)) {
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
        app.services.wish.add(app.currentUserId, productId);
        refreshWishProducts();
        navigation(wishPage->property("ElaPageKey").toString());
    });
}

void MainWindow::refreshProducts()
{
    productGridPage->setProducts(app.services.product.listProducts());
}

void MainWindow::refreshWishProducts()
{
    std::vector<Product> products;
    if (app.currentUserId != 0) {
        for (const int productId : app.repositories.wish.findProductIds(app.currentUserId)) {
            auto product = app.services.product.getProduct(productId);
            if (product.has_value()) {
                products.push_back(*product);
            }
        }
    }
    wishPage->setWishProducts(std::move(products));
}

void MainWindow::refreshCart()
{
    cartWidget->setCart(app.currentUserId == 0 ? Cart() : app.services.cart.cart(app.currentUserId));
}

bool MainWindow::requireLogin()
{
    if (app.currentUserId != 0) {
    if (app.currentUserId != 0) {
        return true;
    }

    loginPage->setStatus("Login required.");
    navigation(loginPage->property("ElaPageKey").toString());
    return false;
}
