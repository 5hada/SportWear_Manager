#include "mainwindow.h"

#include "ElaPushButton.h"
#include "messageBar.h"

#include "app/eventHandler.h"

#include "model/product/cartAction.h"
#include "model/product/category.h"
#include "model/product/product.h"
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
    setUserInfoCardTitle(QString::fromStdString(event.getName()));
    setUserInfoCardSubTitle("Not signed in");

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
                    productGridPage->setProducts(event.getAll());
                    productPages->setCurrentWidget(productGridPage);
                    return;
                }
                if (nodeKey == wishPage->property("ElaPageKey").toString()) {
                    wishPage->setWishs(event.getWishAll());
                    return;
                }
                if (nodeKey == cartPage->property("ElaPageKey").toString()) {
                    cartWidget->setCart(event.getCart());
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
    connect(profilePanel, &ProfilePanel::trySignup, this, [this](const QString& name, const QString& password) {
        const auto success = event.signup(name.toStdString(), password.toStdString());
        if (!success) {
            MessageBar::Fail(this);
            return;
        }

        setUserInfoCardTitle(QString::fromStdString(event.getName()));
        setUserInfoCardSubTitle(QString("Point %1\nSigned in.").arg(event.getPoint()));
        profilePanel->hide();
        showProductPage();
    });
    connect(profilePanel, &ProfilePanel::tryLogin, this, [this](const QString& name, const QString& password) {
        const auto success = event.login(name.toStdString(), password.toStdString());
        if (!success) {
            MessageBar::Fail(this);
            return;
        }

        setUserInfoCardTitle(QString::fromStdString(event.getName()));
        setUserInfoCardSubTitle(QString("Point %1\nSigned in.").arg(event.getPoint()));
        profilePanel->hide();
        showProductPage();
    });
    connect(profilePanel, &ProfilePanel::tryLogout, this, [this]() {
        const auto success = event.logout();
        if (!success) {
            MessageBar::Fail(this);
            return;
        }

        setUserInfoCardTitle(QString::fromStdString(event.getName()));
        setUserInfoCardSubTitle("Not signed in");
        profilePanel->hide();
        showProductPage();
    });

    connect(dialog, &Dialog::rightClicked, this, [=]() {
        event.logout();
        setUserInfoCardTitle("Guest");
        setUserInfoCardSubTitle("Not signed in");
        MessageBar::Logout(this);
    });

    connect(productGridPage, &ProductGridPage::productSelected, this, [this](const Product& product) {
        productDetailPage->setProduct(product);
        productPages->setCurrentWidget(productDetailPage);
    });

    connect(productDetailPage, &ProductDetailPage::cartRequest, this, [this](int productId) {
        if (!event.handleCart(CartAction::Add, productId, 1)) {
            MessageBar::Fail(this);
            return;
        }
        cartWidget->show();
    });

    connect(productDetailPage, &ProductDetailPage::wishRequest, this, [this](int productId) {
        event.setWish(productId);
    });
}

void MainWindow::showProductPage() {
    productGridPage->setProducts(event.getAll());
    productPages->setCurrentWidget(productGridPage);
    navigation(productPages->property("ElaPageKey").toString());
}

void MainWindow::showProductCategoryPage(Category category) {
    
}

void MainWindow::showDetailPage(int productId) {
   productDetailPage->setProduct(event.getProduct(productId));
//    navigation(detailPage)
}

void MainWindow::showCartPage() {
    cartWidget->setCart(event.getCart());
    navigation(cartPage->property("ElaPageKey").toString());
}

void MainWindow::showWishPage() {
    wishPage->setWishs(event.getWishAll());
    navigation(wishPage->property("ElaPageKey").toString());
}

void MainWindow::showOrderPanel() {
    
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
    profilePanel->show(event.isLoggedIn() ? UserRole::User : UserRole::Guest);
}
