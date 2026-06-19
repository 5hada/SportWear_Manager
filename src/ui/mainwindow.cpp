#include "mainwindow.h"

#include "ElaPushButton.h"
#include "messageBar.h"
// #include <ElaProgressRing.h>
#include <QVBoxLayout>

#include "app/eventHandler.h"

#include "model/actions.h"
#include "model/product/category.h"

#include "model/user/user.h"
#include "page/productDetailPage.h"
#include "page/productGridPage.h"
#include "page/profilePanel.h"
#include "page/orderPanel.h"
#include "page/receiptPage.h"
#include "page/wishPage.h"
#include "page/cart/cartWidget.h"
#include "page/cart//cartPage.h"
#include "page/settingPanel.h"

#include "dialog.h"
#include "messageBar.h"
#include "ui/messageBar.h"

#include <ElaDef.h>
#include <ElaIcon.h>
#include <ElaText.h>
#include <QMessageBox>
#include <QRect>
#include <QTimer>
#include <functional>
#include <optional>
#include <qobject.h>
#include <qpoint.h>
#include <qstackedwidget.h>

MainWindow::MainWindow(EventHandler& event): event(event) {
    initWindow();
    initContent();
    connectNavigation();
    connectPageRequests();
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

// void MainWindow::showLoading() {
//     progressRing = new ElaProgressRing(this);
//     progressRing->setFixedSize(100, 100);
//     progressRing->move((width() - progressRing->width()) / 2, (height() - progressRing->height()) / 2);
//     progressRing->show();
//     auto* loadingText = new ElaText("Loading...", this);
//     loadingText->setTextPixelSize(24);
//     loadingText->setAlignment(Qt::AlignCenter);
//     auto* loadingLayout = new QVBoxLayout();
//     loadingLayout->addWidget(loadingText);
//     loadingLayout->addWidget(progressRing);
//     setLayout(loadingLayout);
// }

// void MainWindow::hideLoading() {
//     if (progressRing) {
//         progressRing->deleteLater();
//         progressRing = nullptr;
//     }
//     if (layout()) {
//         delete layout();
//     }
// }

void MainWindow::initContent() {
    updateUserInfo();

    productPages = new QStackedWidget(this);
    productGridPage = new ProductGridPage(event.getItemsPerPage(), this);
    refreshProductPage();
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

    settingPanel = new SettingPanel(this);
    settingPanel->hide();

    cartButton  = new ElaPushButton{this};
    cartButton->setFixedWidth(50);
    adjustCartButton();

    addPageNode("Home", productPages, ElaIconType::House);
    homeKey = productPages->property("ElaPageKey").toString();

    addPageNode("Products", productPages, ElaIconType::Shirt);
    productsKey = productPages->property("ElaPageKey").toString();
    addPageNode("Wish", wishPage, ElaIconType::Heart);
    addPageNode("Cart", cartPage, ElaIconType::CartShopping);
    addPageNode("Orders", receiptPage, ElaIconType::ClockRotateLeft);

    addFooterNode("User", profileKey, 0,ElaIconType::User);
    addFooterNode("Settings", settingKey, 0,ElaIconType::GearComplex);
    
    addDockWidget(Qt::RightDockWidgetArea, cartWidget);
}

void MainWindow::connectNavigation() {
    connect(this, &MainWindow::userInfoCardClicked, this, [=]() {
        showProfilePanel();
    });
    connect(this, &ElaWindow::navigationNodeClicked, this,
            [this](ElaNavigationType::NavigationNodeType, const QString& nodeKey) {
                QTimer::singleShot(0, this, [this, nodeKey]() {
                    if (nodeKey == homeKey || nodeKey == productsKey) {
                        refreshProductPage();
                        productPages->setCurrentWidget(productGridPage);
                    }
                    else if (nodeKey == wishPage->property("ElaPageKey").toString()) {
                        wishPage->setWishs(event.getWishs());
                    }
                    else if (nodeKey == cartPage->property("ElaPageKey").toString()) {
                        cartPage->setCart(event.getCart());
                    }
                    else if (nodeKey == receiptPage->property("ElaPageKey").toString()) {
                        receiptPage->setReceipts(event.getReceipts());
                    }
                    else if (nodeKey == settingKey) {
                        showSettingPanel();
                    }
                    else if (nodeKey == profileKey) {
                        showProfilePanel();
                    }
                    closeCartWidget();
                });
            }
        );
}

void MainWindow::connectPageRequests() {
    connectProductsPage();
    connectDetailPage();
    connectReceiptPage();
    connectCartPage();
    connectWishPage();

    connectOrderPanel();
    connectSettingPanel();
    connectProfilePanel();
    connectCartWidget();
}

void MainWindow::connectProductsPage() {
    connect(productGridPage, &ProductGridPage::productSelected, this, [this](int productId) {
        handleResult(event.setProduct(productId), [this] {
            showDetailPage();
        });
    });
    connect(productGridPage, &ProductGridPage::searchRequested, this, [this](const string& keyword) {
        currentKeyword = keyword.empty() ? std::nullopt : std::make_optional(keyword);
        refreshProductPage();
    });
    connect(productGridPage, &ProductGridPage::categoryChanged, this, [this](Category category) {
        currentCategory = category;
        refreshProductPage();
    });
    connect(productGridPage, &ProductGridPage::pageIndexChanged, this, [this](int newIndex) {
        refreshProductPage(newIndex);
    });
}

void MainWindow::connectDetailPage() {
    connect(productDetailPage, &ProductDetailPage::backRequest, this, [this]() {
        showProductPage();
    });

    connect(productDetailPage, &ProductDetailPage::cartRequest, this, [this](int productId) {
        handleResult(event.handleCart(CartAction::Add, productId, 1), [this] {
            openCartWidget();
        });
    });

    connect(productDetailPage, &ProductDetailPage::orderRequest, this, [this](int productId, int count) {
        handleResult(event.setOrder(productId), [this] {
            showOrderPanel();
        });
    });

    connect(productDetailPage, &ProductDetailPage::wishRequest, this, [this](int productId, bool isWished) {
        handleResult(event.setWish(productId, isWished), [this] {
            productDetailPage->setProduct(event.getProduct(), event.isWished(event.getProduct().getId()));
            wishPage->setWishs(event.getWishs());
        });
    });
}

void MainWindow::connectReceiptPage() {
    connect(receiptPage, &ReceiptPage::refundRequested, this, [this](int receiptId) {
        handleResult(event.refund(receiptId), [this] {
            showReceiptPage();
            updateUserInfo();
        });
    });
}

void MainWindow::connectCartPage() {
    connect(cartPage, &CartPage::orderRequested, this, [this]() {
        handleResult(event.setOrder(), [this] {
            showOrderPanel();
        });
    });

    connect(cartPage, &CartPage::cartRequest, this, [this](CartAction action, int productId, int count, std::optional<bool> isSelected) {
        handleResult(event.handleCart(action, productId, count, isSelected));
    });
}

void MainWindow::connectWishPage() {
    connect(wishPage, &WishPage::productSelected, this, [this](int productId) {
        handleResult(event.setProduct(productId), [this] {
            showDetailPage();
        });
    });

    connect(wishPage, &WishPage::removeRequested, this, [this](int productId) {
        handleResult(event.setWish(productId, false), [this] {
            showWishPage();
        });
    });
}




void MainWindow::connectOrderPanel() {
    connect(orderPanel, &OrderPanel::confirmRequested, this, [this](int usedPoint) {
        handleResult(event.confirmOrder(usedPoint), [this] {
            showReceiptPage();
            orderPanel->hide();
        });
    });

    connect(orderPanel, &OrderPanel::cancelRequested, this, [this]() {
        showCartPage();
    });
}

void MainWindow::connectSettingPanel() {

}

void MainWindow::connectProfilePanel() {
    connect(profilePanel, &ProfilePanel::trySignup, this, [this](const QString& name, const QString& password) {
        handleResult(event.setUser(UserAction::Signup, name.toStdString(), password.toStdString()), [this] {
            updateUserInfo();
        profilePanel->hide();
        });
    });
    connect(profilePanel, &ProfilePanel::tryLogin, this, [this](const QString& name, const QString& password) {
        handleResult(event.setUser(UserAction::Login, name.toStdString(), password.toStdString()), [this] {
            updateUserInfo();
        profilePanel->hide();
        });
    });
    connect(profilePanel, &ProfilePanel::tryLogout, this, [this]() {
        handleResult(event.setUser(UserAction::Logout), [this] {
            updateUserInfo();
        profilePanel->hide();
        });
    });
}

void MainWindow::connectCartWidget() {
    connect(cartButton, &ElaPushButton::pressed, this, [this]() {
        openCartWidget();
    });
}




void MainWindow::showProductPage() {
    refreshProductPage();
    productPages->setCurrentWidget(productGridPage);
    // if (prevNodeKey == getCurrentNavigationPageKey()) {return;}
    if (getCurrentNavigationPageKey() != productsKey){
        navigation(productsKey);
    }

}

void MainWindow::showDetailPage() {
    const auto product = event.getProduct();
    productDetailPage->setProduct(product, event.isWished(product.getId()));
    productPages->setCurrentWidget(productDetailPage);
    if (getCurrentNavigationPageKey() != productsKey){
        navigation(productsKey);
    }
}

void MainWindow::showReceiptPage() {
    receiptPage->setReceipts(event.getReceipts());
    if (getCurrentNavigationPageKey() != receiptPage->property("ElaPageKey").toString()){
        navigation(receiptPage->property("ElaPageKey").toString());
    }
}

void MainWindow::showCartPage() {
    cartPage->setCart(event.getCart());
    if (getCurrentNavigationPageKey() != cartPage->property("ElaPageKey").toString()){
        navigation(cartPage->property("ElaPageKey").toString());
    }
}

void MainWindow::showWishPage() {
    wishPage->setWishs(event.getWishs());
    if (getCurrentNavigationPageKey() != wishPage->property("ElaPageKey").toString()){
        navigation(wishPage->property("ElaPageKey").toString());
    }
}



void MainWindow::showOrderPanel() {
    orderPanel->setOrder(event.getOrder());
    orderPanel->moveToCenter();
    orderPanel->show();
}

void MainWindow::showSettingPanel() {
    movePanelToWindowCenter(settingPanel);
    settingPanel->show();
}

void MainWindow::showProfilePanel() {
    movePanelToWindowCenter(profilePanel);
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

void MainWindow::refreshProductPage(int pageIndex) {
    if (!event.setProducts(pageIndex, currentKeyword, currentCategory)) {
        MessageBar::Fail(this);
        return;
    }
    productGridPage->setCategory(currentCategory);
    productGridPage->setContents(event.getProductsContents());
}

void MainWindow::movePanelToWindowCenter(QWidget* panel) {
    if (panel == nullptr) {
        return;
    }
    const QRect windowRect = frameGeometry();
    const int x = windowRect.x() + (windowRect.width() - panel->width()) / 2;
    const int y = windowRect.y() + (windowRect.height() - panel->height()) / 2;
    panel->move(x, y);
}



void MainWindow::openCartWidget() {
    cartWidget->setCart(event.getCart());
    cartButton->hide();
    cartWidget->showNormal();
}

void MainWindow::closeCartWidget() {
    adjustCartButton();
    cartButton->show();
    cartWidget->hide();
}

void MainWindow::adjustCartButton() {
    cartButton->move(
        this->width() - cartButton->width() - 20,
        this->height() - cartButton->height() - 10
    );
}


void MainWindow::handleResult(bool result, const std::function<void()>& callback) {
    if (result) {
        MessageBar::Success(this);
        if (callback) {callback();}
    }
    else {
        MessageBar::Fail(this);
    }
}
