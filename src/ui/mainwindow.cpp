#include "mainwindow.h"

#include "ElaPushButton.h"
#include "messageBar.h"

#include "app/eventHandler.h"

#include "model/actions.h"
#include "model/product/category.h"
#include "model/product/product.h"
#include "model/user/user.h"
#include "page/productDetailPage.h"
#include "page/productGridPage.h"
#include "page/profilePanel.h"
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
#include <QTimer>
#include <qobject.h>
#include <qpoint.h>
#include <qstackedwidget.h>

MainWindow::MainWindow(EventHandler& event): event(event){
    initWindow();
    initContent();
    connectNavigation();
    connectPages();
}

void MainWindow::initWindow() {
    setWindowTitle("SportWear Manager");
    resize(1200, 760);
    moveToCenter();
    setFocusPolicy(Qt::StrongFocus);

    auto* landingText = new ElaText("SportWear Manager", this);
    landingText->setTextPixelSize(32);
    landingText->setAlignment(Qt::AlignCenter);
    addCentralWidget(landingText);
}

void MainWindow::initContent() {
    updateUserInfo();

    productPages = new QStackedWidget(this);
    productGridPage = new ProductGridPage(this);
    for (auto& category: Categories){
        productCategoryPages.try_emplace(category, new ProductGridPage(this));
    }
    productDetailPage = new ProductDetailPage(this);
    profilePanel = new ProfilePanel(this);
    profilePanel->hide();
    productPages->addWidget(productGridPage);
    productPages->addWidget(productDetailPage);
    productPages->setCurrentWidget(productGridPage);

    orderPanel = new OrderPanel(this);
    orderPanel->hide();
    receiptPage = new ReceiptPage(this);
    cartWidget = new CartWidget(this);
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
        addPageNode(QString::fromStdString(categoryToString(category)), productCategoryPages.at(category), categoriesKey, ElaIconType::Shirt);
    }
    addPageNode("Wish", wishPage, ElaIconType::Heart);
    addPageNode("Cart", cartPage, ElaIconType::CartShopping);
    addPageNode("Orders", receiptPage, ElaIconType::ClockRotateLeft);

    addFooterNode("User", profileKey, 0,ElaIconType::User);
    addFooterNode("Settings", settingsKey, 0,ElaIconType::GearComplex);
    
    addDockWidget(Qt::RightDockWidgetArea, cartWidget);
}

void MainWindow::connectNavigation() {
    connect(this, &MainWindow::userInfoCardClicked, this, [=]() {
        showUserPanel();
        return;
    });

    connect(this, &ElaWindow::navigationNodeClicked, this,
            [this](ElaNavigationType::NavigationNodeType, const QString& nodeKey) {
                if (nodeKey == productPages->property("ElaPageKey").toString()) {
                    if (navigatingToProductDetail) {
                        navigatingToProductDetail = false;
                        return;
                    }
                    productGridPage->setProducts(event.getProducts());
                    productPages->setCurrentWidget(productGridPage);
                    return;
                }
                if (nodeKey == wishPage->property("ElaPageKey").toString()) {
                    wishPage->setWishs(event.getWishs());
                    return;
                }
                if (nodeKey == cartPage->property("ElaPageKey").toString()) {
                    const auto cart = event.getCart();
                    cartPage->setCart(cart);
                    cartWidget->setCart(cart);
                    return;
                }
                if (nodeKey == receiptPage->property("ElaPageKey").toString()) {
                    receiptPage->setReceipts(event.getReceipts());
                    return;
                }
                if (nodeKey == settingsKey) {
                    showUserPanel();
                    return;
                }
                if (nodeKey == profileKey) {
                    showUserPanel();
                    return;
                }
                for (auto& category: Categories){
                    if (nodeKey == productCategoryPages.at(category)->property("ElaPageKey").toString()) {
                        showProductCategoryPage(category);
                        return;
                    }
                }
            }
        );
    

}

void MainWindow::connectPages() {
    const auto refreshCart = [this]() {
        const auto cart = event.getCart();
        cartPage->setCart(cart);
        cartWidget->setCart(cart);
    };
    const auto closeProfileAndShowProducts = [this]() {
        profilePanel->hide();
        QTimer::singleShot(0, this, [this]() {
            showProductPage();
        });
    };

    connect(profilePanel, &ProfilePanel::trySignup, this, [this, closeProfileAndShowProducts](const QString& name, const QString& password) {
        const auto success = event.setUser(UserAction::Signup,name.toStdString(), password.toStdString());
        if (!success) {
            MessageBar::Fail(this);
            return;
        }

        updateUserInfo();
        closeProfileAndShowProducts();
    });
    connect(profilePanel, &ProfilePanel::tryLogin, this, [this, closeProfileAndShowProducts](const QString& name, const QString& password) {
        const auto success = event.setUser(UserAction::Login, name.toStdString(), password.toStdString());
        if (!success) {
            MessageBar::Fail(this);
            return;
        }

        updateUserInfo();
        closeProfileAndShowProducts();
    });
    connect(profilePanel, &ProfilePanel::tryLogout, this, [this, closeProfileAndShowProducts]() {
        const auto success = event.setUser(UserAction::Logout);
        if (!success) {
            MessageBar::Fail(this);
            return;
        }

        updateUserInfo();
        closeProfileAndShowProducts();
    });

    connect(dialog, &Dialog::rightClicked, this, [=]() {
        event.setUser(UserAction::Logout);
        setUserInfoCardTitle("Guest");
        setUserInfoCardSubTitle("Not signed in");
        MessageBar::Logout(this);
    });

    connect(productGridPage, &ProductGridPage::productSelected, this, [this](const Product& product) {
        showDetailPage(product.getId());
    });
    for (auto& [category, page] : productCategoryPages) {
        connect(page, &ProductGridPage::productSelected, this, [this, page](const Product& product) {
            showDetailPage(product.getId(), page->property("ElaPageKey").toString());
        });
    }

    connect(productDetailPage, &ProductDetailPage::backRequested, this, [this]() {
        if (!detailReturnNodeKey.isEmpty()) {
            const QString returnNodeKey = detailReturnNodeKey;
            detailReturnNodeKey.clear();
            navigation(returnNodeKey);
            return;
        }
        productPages->setCurrentWidget(productGridPage);
    });

    connect(productDetailPage, &ProductDetailPage::cartRequest, this, [this](int productId) {
        if (!event.handleCart(CartAction::Add, productId, 1)) {
            MessageBar::Fail(this);
            return;
        }
        cartWidget->setCart(event.getCart());
        cartWidget->show();
    });

    connect(productDetailPage, &ProductDetailPage::orderRequest, this, [this](int productId, int count) {
        showOrderPanel(event.getOrder(productId));
    });

    connect(productDetailPage, &ProductDetailPage::wishRequest, this, [this](int productId) {
        if (!event.setWish(productId)) {
            MessageBar::Fail(this);
            return;
        }
        MessageBar::Success(this);
        wishPage->setWishs(event.getWishs());
    });

    connect(wishPage, &WishPage::productSelected, this, [this](int productId) {
        showDetailPage(productId, wishPage->property("ElaPageKey").toString());
    });

    connect(wishPage, &WishPage::removeRequested, this, [this](int productId) {
        if (!event.setWish(productId, false)) {
            MessageBar::Fail(this);
            return;
        }
        wishPage->setWishs(event.getWishs());
        MessageBar::Success(this);
    });

    connect(cartPage, &CartPage::orderRequested, this, [this]() {
        showOrderPanel(event.getOrder());
    });

    connect(cartPage, &CartPage::increaseRequested, this, [this, refreshCart](int productId) {
        if (!event.handleCart(CartAction::Add, productId, 1)) {
            MessageBar::Fail(this);
            return;
        }
        refreshCart();
    });

    connect(cartPage, &CartPage::decreaseRequested, this, [this, refreshCart](int productId) {
        if (!event.handleCart(CartAction::Sub, productId, 1)) {
            MessageBar::Fail(this);
            return;
        }
        refreshCart();
    });

    connect(cartPage, &CartPage::toggleSelectedRequested, this, [this, refreshCart](int productId, bool isSelected) {
        if (!event.handleCart(CartAction::Toggle, productId, 0, isSelected)) {
            MessageBar::Fail(this);
            return;
        }
        refreshCart();
    });

    connect(cartPage, &CartPage::removeRequested, this, [this, refreshCart](int productId) {
        if (!event.handleCart(CartAction::Del, productId)) {
            MessageBar::Fail(this);
            return;
        }
        refreshCart();
    });

    connect(cartPage, &CartPage::clearRequested, this, [this, refreshCart]() {
        if (!event.handleCart(CartAction::Clear)) {
            MessageBar::Fail(this);
            return;
        }
        refreshCart();
    });

    connect(orderPanel, &OrderPanel::confirmRequested, this, [this](int usedPoint) {
        if (!event.confirmOrder(usedPoint)) {
            MessageBar::Fail(this);
            return;
        }
        orderPanel->hide();
        cartWidget->setCart(event.getCart());
        showReceiptPage();
    });

    connect(orderPanel, &OrderPanel::cancelRequested, this, [this]() {
        showCartPage();
    });

    connect(receiptPage, &ReceiptPage::refundRequested, this, [this](int receiptId) {
        if (!event.refund(receiptId)) {
            MessageBar::Fail(this);
            return;
        }
        receiptPage->setReceipts(event.getReceipts());
        updateUserInfo();
        MessageBar::Success(this);
    });
}

void MainWindow::showProductPage() {
    productGridPage->setProducts(event.getProducts());
    productPages->setCurrentWidget(productGridPage);
    navigation(productPages->property("ElaPageKey").toString());
}

void MainWindow::showProductCategoryPage(Category category) {
    auto* page = productCategoryPages.at(category);
    page->setProducts(event.getProducts(std::nullopt, category));
}

void MainWindow::showDetailPage(int productId, const QString& returnNodeKey) {
   detailReturnNodeKey = returnNodeKey;
   productDetailPage->setProduct(event.getProduct(productId));
   productPages->setCurrentWidget(productDetailPage);
   navigatingToProductDetail = true;
   navigation(productPages->property("ElaPageKey").toString());
}

void MainWindow::showCartPage() {
    const auto cart = event.getCart();
    cartPage->setCart(cart);
    cartWidget->setCart(cart);
    navigation(cartPage->property("ElaPageKey").toString());
}

void MainWindow::showWishPage() {
    wishPage->setWishs(event.getWishs());
    navigation(wishPage->property("ElaPageKey").toString());
}

void MainWindow::showOrderPanel(const Order& order) {
    if (order.getItems().empty()) {
        MessageBar::Fail(this);
        return;
    }
    orderPanel->setOrder(order);
    orderPanel->moveToCenter();
    orderPanel->show();
}

void MainWindow::showReceiptPage() {
    receiptPage->setReceipts(event.getReceipts());
    navigation(receiptPage->property("ElaPageKey").toString());
}

void MainWindow::adjustCartButton() {
    cartButton->move(
        this->width() - cartButton->width() - 20,
        this->height() - cartButton->height() - 10
    );
}

void MainWindow::showUserPanel() {
    profilePanel->show(event.getUser().getRole());
}

void MainWindow::updateUserInfo() {
    UserInfo info = event.getUser();
    setUserInfoCardTitle(QString::fromStdString(info.getName()));
    switch (info.getRole()){
        case UserRole::User:
            setUserInfoCardSubTitle(QString("Point %1\nSigned in.").arg(info.getPoint()));
            break;
        case UserRole::Admin:
            setUserInfoCardSubTitle(QString("Point %1\nSigned in. ADMINSTRATOR").arg(info.getPoint()));
            break;
        case UserRole::Guest:
            setUserInfoCardSubTitle("Not signed in");   
            break;
    }
}
