#include "mainwindow.h"

#include "app/eventHandler.h"

#include "model/actions.h"
#include "model/product/category.h"
#include "model/ui/userInfo.h"

#include "ui/components/dialog.h"
#include "ui/components/messageBar.h"
#include "ui/pages/product/productPages.h"
#include "ui/pages/profile/profilePanel.h"
#include "ui/pages/order/orderPanel.h"
#include "ui/pages/order/receiptPage.h"
#include "ui/pages/wish/wishPage.h"
#include "ui/pages/cart/cartWidget.h"
#include "ui/pages/cart/cartPage.h"
#include "ui/pages/settings/settingPanel.h"

#include "ElaPushButton.h"
#include <ElaDef.h>
#include <ElaIcon.h>
#include <ElaText.h>
#include <QPixmap>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRect>
#include <QTimer>

MainWindow::MainWindow(EventHandler& event): event(event) {
    initWindow();
    initContent();
    connectNavigation();
    connectPageRequests();
}

void MainWindow::initWindow() {
    setWindowTitle("SportWear Manager");
    setUserInfoCardPixmap(QPixmap(":/images/avatar.png"));
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

    productPages = new ProductPages(event.getItemsPerPage(), this);
    refreshProductPage();
    profilePanel = new ProfilePanel(this);
    profilePanel->hide();

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
    updateAdminControls();
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
                        productPages->showGrid();
                    }
                    else if (nodeKey == wishPage->property("ElaPageKey").toString()) {
                        refreshWishPageContents();
                    }
                    else if (nodeKey == cartPage->property("ElaPageKey").toString()) {
                        if (!event.canUseCart()) {
                            MessageBar::Fail(this);
                            showProductPage();
                            return;
                        }
                        refreshCartPageContents();
                    }
                    else if (nodeKey == receiptPage->property("ElaPageKey").toString()) {
                        refreshReceiptPageContents();
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
    connectEditPage();
    connectReceiptPage();
    connectCartPage();
    connectWishPage();

    connectOrderPanel();
    connectSettingPanel();
    connectProfilePanel();
    connectCartWidget();
}

void MainWindow::connectProductsPage() {
    connect(productPages, &ProductPages::productSelected, this, [this](int productId) {
        handleResult(event.setProduct(productId), [this] {
            showDetailPage();
        });
    });
    connect(productPages, &ProductPages::searchRequested, this, [this](const std::string& keyword) {
        currentKeyword = keyword.empty() ? std::nullopt : std::make_optional(keyword);
        refreshProductPage();
    });
    connect(productPages, &ProductPages::categoryChanged, this, [this](Category category) {
        currentCategory = category;
        refreshProductPage();
    });
    connect(productPages, &ProductPages::pageIndexChanged, this, [this](int newIndex) {
        refreshProductPage(newIndex);
    });
    connect(productPages, &ProductPages::addRequested, this, [this]() {
        showProductAddPage();
    });
}

void MainWindow::connectDetailPage() {
    connect(productPages, &ProductPages::backRequested, this, [this]() {
        showProductPage();
    });

    connect(productPages, &ProductPages::cartRequested, this, [this](int productId) {
        handleResult(event.handleCart(CartAction::Add, productId, 1), [this] {
            openCartWidget();
        });
    });

    connect(productPages, &ProductPages::orderRequested, this, [this](int productId, int count) {
        handleResult(event.setOrder(productId), [this] {
            showOrderPanel();
        });
    });

    connect(productPages, &ProductPages::wishRequested, this, [this](int productId, bool isWished) {
        handleResult(event.setWish(productId, isWished), [this] {
            const auto content = event.getProductDetailContent();
            productPages->setProductContent(content);
            refreshProductDetailReviews(content.id);
            refreshWishPageContents();
        });
    });
    connect(productPages, &ProductPages::editRequested, this, [this](int productId) {
        handleResult(event.setProduct(productId), [this] {
            showProductEditPage();
        });
    });
    connect(productPages, &ProductPages::reviewSaveRequested,
            this, [this](int reviewId, int productId, int rating, const QString& comment) {
        handleResult(event.saveReview(reviewId, productId, rating, comment.toStdString()), [this, productId] {
            QTimer::singleShot(0, this, [this, productId]() {
                refreshProductDetailReviews(productId);
            });
        });
    });
    connect(productPages, &ProductPages::reviewDeleteRequested, this, [this](int reviewId) {
        const int productId = event.getCurrentProductId();
        handleResult(event.deleteReview(reviewId), [this, productId] {
            QTimer::singleShot(0, this, [this, productId]() {
                refreshProductDetailReviews(productId);
            });
        });
    });
}

void MainWindow::connectEditPage() {
    connect(productPages, &ProductPages::productSaveRequested,
            this, [this](int productId, const QString& name, Category category, int price, int stock, const QString& detail) {
        const bool isEdit = productId > 0;
        handleResult(event.updateProductForm(productId, name.toStdString(), category, price, stock, detail.toStdString()), [this, productId, isEdit] {
            refreshProductPage();
            if (isEdit) {
                event.setProduct(productId);
                showDetailPage();
            }
            else {
                showProductPage();
            }
        });
    });
    connect(productPages, &ProductPages::productCancelRequested, this, [this]() {
        if (productEditReturnToDetail) {
            showDetailPage();
        }
        else {
            showProductPage();
        }
    });
}

void MainWindow::connectReceiptPage() {
    connect(receiptPage, &ReceiptPage::pageMoveRequested, this, [this](int delta) {
        receiptPage->refreshContent(event.moveReceiptPage(delta));
    });
    connect(receiptPage, &ReceiptPage::refundRequested, this, [this](int receiptId) {
        handleResult(event.refund(receiptId), [this] {
            QTimer::singleShot(0, this, [this]() {
                refreshReceiptPageContents();
                updateUserInfo();
            });
        });
    });
}

void MainWindow::connectCartPage() {
    connect(cartPage, &CartPage::pageMoveRequested, this, [this](int delta) {
        cartPage->refreshContent(event.moveCartPage(delta));
    });
    connect(cartPage, &CartPage::orderRequested, this, [this]() {
        handleResult(event.setOrder(), [this] {
            showOrderPanel();
        });
    });

    connect(cartPage, &CartPage::cartRequest, this, [this](CartAction action, int productId, int count, std::optional<bool> isSelected) {
        if (!event.handleCart(action, productId, count, isSelected)) {
            QTimer::singleShot(0, this, [this]() {
                refreshCartPageContents();
            });
            MessageBar::Fail(this);
            return;
        }
        MessageBar::Success(this);
        QTimer::singleShot(0, this, [this]() {
            refreshCartPageContents();
            cartWidget->setContent(event.getCartWidgetContent());
        });
    });
}

void MainWindow::connectWishPage() {
    connect(wishPage, &WishPage::pageMoveRequested, this, [this](int delta) {
        wishPage->refreshContent(event.moveWishPage(delta));
    });
    connect(wishPage, &WishPage::cartRequested, this, [this](int productId) {
        handleResult(event.handleCart(CartAction::Add, productId, 1), [this] {
            QTimer::singleShot(0, this, [this]() {
                refreshWishPageContents();
                cartWidget->setContent(event.getCartWidgetContent());
                openCartWidget();
            });
        });
    });

    connect(wishPage, &WishPage::removeRequested, this, [this](int productId) {
        handleResult(event.setWish(productId, false), [this] {
            QTimer::singleShot(0, this, [this]() {
                refreshWishPageContents();
            });
        });
    });
}




void MainWindow::connectOrderPanel() {
    connect(orderPanel, &OrderPanel::pointChanged, this, [this](int usedPoint) {
        orderPanel->setPayment(event.getOrderPayment(usedPoint));
    });

    connect(orderPanel, &OrderPanel::confirmRequested, this, [this](int usedPoint) {
        handleResult(event.confirmOrder(usedPoint), [this] {
            showReceiptPage();
            updateUserInfo();
            refreshCartPageContents();
            cartWidget->setContent(event.getCartWidgetContent());
            refreshProductPage();
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
    connect(cartWidget, &CartWidget::visibilityChanged, this, [this](bool visible) {
        if (!visible) {
            adjustCartButton();
            cartButton->setVisible(event.canUseCart());
        }
    });
}




void MainWindow::showProductPage() {
    refreshProductPage();
    productPages->showGrid();
    // if (prevNodeKey == getCurrentNavigationPageKey()) {return;}
    if (getCurrentNavigationPageKey() != productsKey){
        navigation(productsKey);
    }

}

void MainWindow::showDetailPage() {
    const auto content = event.getProductDetailContent();
    productPages->setProductContent(content);
    refreshProductDetailReviews(content.id);
    updateAdminControls();
    productPages->showDetail();
    if (getCurrentNavigationPageKey() != productsKey){
        navigation(productsKey);
    }
}

void MainWindow::showProductAddPage() {
    if (!event.canManageProducts()) {
        MessageBar::Fail(this);
        return;
    }
    productEditReturnToDetail = false;
    productPages->showAddForm();
    if (getCurrentNavigationPageKey() != productsKey){
        navigation(productsKey);
    }
}

void MainWindow::showProductEditPage() {
    if (!event.canManageProducts()) {
        MessageBar::Fail(this);
        return;
    }
    productEditReturnToDetail = true;
    productPages->showEditForm(event.getProductFormContent());
    if (getCurrentNavigationPageKey() != productsKey){
        navigation(productsKey);
    }
}

void MainWindow::showReceiptPage() {
    refreshReceiptPageContents();
    if (getCurrentNavigationPageKey() != receiptPage->property("ElaPageKey").toString()){
        navigation(receiptPage->property("ElaPageKey").toString());
    }
}

void MainWindow::showCartPage() {
    if (!event.canUseCart()) {
        MessageBar::Fail(this);
        showProductPage();
        return;
    }
    refreshCartPageContents();
    if (getCurrentNavigationPageKey() != cartPage->property("ElaPageKey").toString()){
        navigation(cartPage->property("ElaPageKey").toString());
    }
}

void MainWindow::showWishPage() {
    refreshWishPageContents();
    if (getCurrentNavigationPageKey() != wishPage->property("ElaPageKey").toString()){
        navigation(wishPage->property("ElaPageKey").toString());
    }
}



void MainWindow::showOrderPanel() {
    orderPanel->setContent(event.getOrderPanelContent());
    orderPanel->moveToCenter();
    orderPanel->show();
}

void MainWindow::showSettingPanel() {
    movePanelToWindowCenter(settingPanel);
    settingPanel->show();
}

void MainWindow::showProfilePanel() {
    movePanelToWindowCenter(profilePanel);
    profilePanel->show(event.getUser());
}

void MainWindow::updateUserInfo() {
    UserInfo info = event.getUser();
    setUserInfoCardTitle(QString::fromStdString(info.getName()));
    switch (info.getRole()){
        case UiUserRole::User:
            setUserInfoCardSubTitle(QString("Point %1\nSigned in.").arg(info.getPoint()));
            break;
        case UiUserRole::Admin:
            setUserInfoCardSubTitle(QString("Point %1\nSigned in. ADMINSTRATOR").arg(info.getPoint()));
            break;
        case UiUserRole::Guest:
            setUserInfoCardSubTitle("Not signed in");   
            break;
    }
    updateAdminControls();
    if (productPages != nullptr && productPages->isDetailVisible()) {
        const int productId = event.getCurrentProductId();
        if (productId > 0) {
            refreshProductDetailReviews(productId);
        }
    }
}

void MainWindow::refreshProductPage(int pageIndex) {
    if (!event.setProducts(pageIndex, currentKeyword, currentCategory)) {
        MessageBar::Fail(this);
        return;
    }
    productPages->setGridCategory(currentCategory);
    productPages->setGridContents(event.getProductsContents());
}

void MainWindow::refreshProductDetailReviews(int productId) {
    productPages->setReviewContent(event.getReviewContent(productId));
}

void MainWindow::refreshCartPageContents() {
    cartPage->refreshContent(event.getCartPageContent());
}

void MainWindow::refreshWishPageContents() {
    wishPage->refreshContent(event.getWishPageContent());
}

void MainWindow::refreshReceiptPageContents() {
    receiptPage->refreshContent(event.getReceiptPageContent());
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

void MainWindow::updateAdminControls() {
    const bool isAdmin = event.canManageProducts();
    const bool canUseCart = event.canUseCart();
    if (productPages != nullptr) {
        productPages->setAdminMode(isAdmin);
        productPages->setCartAvailable(canUseCart);
        productPages->setWishAvailable(canUseCart);
    }
    if (cartButton != nullptr) {
        cartButton->setVisible(canUseCart && (cartWidget == nullptr || !cartWidget->isVisible()));
    }
    if (!canUseCart && cartWidget != nullptr) {
        cartWidget->hide();
    }
}



void MainWindow::openCartWidget() {
    if (!event.canUseCart()) {
        MessageBar::Fail(this);
        cartButton->hide();
        cartWidget->hide();
        return;
    }
    cartWidget->setContent(event.getCartWidgetContent());
    cartButton->hide();
    cartWidget->showNormal();
}

void MainWindow::closeCartWidget() {
    adjustCartButton();
    cartButton->setVisible(event.canUseCart());
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
