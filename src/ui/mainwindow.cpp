#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTabWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    buildInterface();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::buildInterface() {
    setWindowTitle("SportWear Manager");
    resize(900, 640);

    auto *rootLayout = new QVBoxLayout(ui->centralwidget);
    sessionLabel_ = new QLabel("Not signed in", ui->centralwidget);
    tabs_ = new QTabWidget(ui->centralwidget);

    loginPage =
        new LoginPage(app, this);

    tabs_->addTab(loginPage, "Login");
    tabs_->addTab(productTab, "Products");
    tabs_->addTab(cartTab, "Cart");
    tabs_->addTab(orderTab, "Orders");
    tabs_->addTab(reviewTab, "Reviews");

    rootLayout->addWidget(sessionLabel_);
    rootLayout->addWidget(tabs_);

    connect(loginButton, &QPushButton::clicked, this, [this]() {
        const auto user = loginService_.login(usernameEdit_->text().toStdString(),
                                             passwordEdit_->text().toStdString());
        if (!user.has_value()) {
            QMessageBox::warning(this, "Login failed", "Check ID and password.");
            return;
        }
        app.currentUserId = user->id();
        sessionLabel_->setText("Signed in: " + QString::fromStdString(user->name())
                               + " / Point: " + QString::number(user->point()));
        tabs_->setCurrentIndex(1);
        refreshCart();
        refreshOrders();
    });

    connect(addCartButton, &QPushButton::clicked, this, [this]() {
        if (!requireLogin()) {
            return;
        }
        const int productId = selectedProductId();
        if (productId == 0 || !cartService_.addProduct(app.currentUserId, productId, quantitySpin_->value())) {
            QMessageBox::warning(this, "Cart", "Select an in-stock product.");
            return;
        }
        refreshCart();
        tabs_->setCurrentIndex(2);
    });

    connect(removeCartButton, &QPushButton::clicked, this, [this]() {
        if (!requireLogin() || cartList_->currentItem() == nullptr) {
            return;
        }
        cartService_.removeProduct(app.currentUserId, cartList_->currentItem()->data(Qt::UserRole).toInt());
        refreshCart();
    });

    connect(clearCartButton, &QPushButton::clicked, this, [this]() {
        if (requireLogin()) {
            cartService_.clear(app.currentUserId);
            refreshCart();
        }
    });

    connect(checkoutButton, &QPushButton::clicked, this, [this]() {
        if (!requireLogin()) {
            return;
        }
        const auto order = orderService_.checkout(app.currentUserId, Delivery(addressEdit_->text().toStdString()));
        if (!order.has_value()) {
            QMessageBox::warning(this, "Checkout", "Cart is empty or stock is not enough.");
            return;
        }
        addressEdit_->clear();
        refreshProducts();
        refreshCart();
        refreshOrders();
        tabs_->setCurrentIndex(3);
    });

    connect(reviewButton, &QPushButton::clicked, this, [this]() {
        if (!requireLogin()) {
            return;
        }
        const int productId = selectedProductId();
        if (productId == 0 || reviewCommentEdit_->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Review", "Select a product and enter a comment.");
            return;
        }
        reviewService_.addReview(app.currentUserId,
                                 productId,
                                 reviewRatingSpin_->value(),
                                 reviewCommentEdit_->text().toStdString());
        reviewCommentEdit_->clear();
        refreshReviews();
    });

    connect(productList_, &QListWidget::currentRowChanged, this, [this]() {
        refreshReviews();
    });
}



int MainWindow::selectedProductId() const
{
    if (productList_ == nullptr || productList_->currentItem() == nullptr) {
        return 0;
    }
    return productList_->currentItem()->data(Qt::UserRole).toInt();
}

bool MainWindow::requireLogin()
{
    if (app.currentUserId != 0) {
        return true;
    }
    QMessageBox::information(this, "Login required", "Sign in first.");
    tabs_->setCurrentIndex(0);
    return false;
}
