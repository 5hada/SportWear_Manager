#include "mainwindow.h"

#include "ElaPushButton.h"
#include "messageBar.h"
// #include <ElaProgressRing.h>
#include <QVBoxLayout>

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
#include "page/settingPanel.h"

#include "dialog.h"
#include "messageBar.h"
#include "ui/messageBar.h"

#include <ElaDef.h>
#include <ElaIcon.h>
#include <ElaText.h>
#include <QMessageBox>
#include <QTimer>
#include <functional>
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

    for (auto& category: Categories){
        productsKeys.insert_or_assign(category, QString::fromStdString(categoryToString(category)));
    }

    productPages = new QStackedWidget(this);
    productGridPage = new ProductGridPage(event.getItemsPerPage(), this);

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

    addPageNode("Products", productPages, ElaIconType::Shirt);
    addExpanderNode("Categories", categoriesKey, ElaIconType::GridRound2);
    for (auto& category: Categories){
        if (category == Category::Unknown) {
            continue;
        }
        addPageNode(QString::fromStdString(categoryToString(category)), productsKeys.at(category), categoriesKey, ElaIconType::Shirt);
    }
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
                if (nodeKey == productPages->property("ElaPageKey").toString()) {
                    prevNodeKey = nodeKey;
                    showProductPage();
                }
                else if (nodeKey == wishPage->property("ElaPageKey").toString()) {
                    showWishPage();
                }
                else if (nodeKey == cartPage->property("ElaPageKey").toString()) {
                    showCartPage();
                }
                else if (nodeKey == receiptPage->property("ElaPageKey").toString()) {
                    showReceiptPage();
                }
                else if (nodeKey == settingKey) {
                    showSettingPanel();
                }
                else if (nodeKey == profileKey) {
                    showProfilePanel();
                }
                else{
                    for (auto& category: Categories){
                        if (nodeKey == productsKeys.at(category)->property("ElaPageKey").toString()) {
                            prevNodeKey = nodeKey;
                            showProductPage();
                            break;
                        }
                    }
                }
                closeCartWidget();
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
    connect(productGridPage, &ProductGridPage::productSelected, this, [this](const Product& product) {
        handleResult(event.setProduct(product.getId()), [this] {
            showDetailPage();
        });
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

    connect(productDetailPage, &ProductDetailPage::wishRequest, this, [this](int productId) {
        handleResult(event.setWish(productId));
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
        });
    });
    connect(profilePanel, &ProfilePanel::tryLogin, this, [this](const QString& name, const QString& password) {
        handleResult(event.setUser(UserAction::Login, name.toStdString(), password.toStdString()), [this] {
            updateUserInfo();
        });
    });
    connect(profilePanel, &ProfilePanel::tryLogout, this, [this]() {
        handleResult(event.setUser(UserAction::Logout), [this] {
            updateUserInfo();
        });
    });
}

void MainWindow::connectCartWidget() {
    connect(cartButton, &ElaPushButton::pressed, this, [this]() {
        openCartWidget();
    });
}




void MainWindow::showProductPage() {
    productGridPage->setContents(event.getProductsContents());
    productPages->setCurrentWidget(productGridPage);
    // if (prevNodeKey == getCurrentNavigationPageKey()) {return;}
    if (getCurrentNavigationPageKey() != productPages->property("ElaPageKey").toString()){
        navigation(productPages->property("ElaPageKey").toString());
    }

}

void MainWindow::showDetailPage() {
    productDetailPage->setProduct(event.getProduct());
    productPages->setCurrentWidget(productDetailPage);
    if (getCurrentNavigationPageKey() != productPages->property("ElaPageKey").toString()){
        navigation(productPages->property("ElaPageKey").toString());
    }
}

void MainWindow::showReceiptPage() {
    receiptPage->setReceipts(event.getReceipts());
    navigation(receiptPage->property("ElaPageKey").toString());
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
    settingPanel->moveToCenter();
    settingPanel->show();
}

void MainWindow::showProfilePanel() {
    profilePanel->moveToCenter();
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
    profilePanel->hide();
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