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
    , ui(new Ui::MainWindow)
    , loginService_(&userRepository_)
    , productService_(&productRepository_)
    , cartService_(&cartRepository_, &productRepository_)
    , orderService_(&orderRepository_, &cartRepository_, &productRepository_, &paymentRepository_)
    , reviewService_(&reviewRepository_)
{
    ui->setupUi(this);
    buildInterface();
    refreshProducts();
    refreshCart();
    refreshOrders();
    refreshReviews();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildInterface()
{
    setWindowTitle("SportWear Manager");
    resize(900, 640);

    auto *rootLayout = new QVBoxLayout(ui->centralwidget);
    sessionLabel_ = new QLabel("Not signed in", ui->centralwidget);
    tabs_ = new QTabWidget(ui->centralwidget);

    auto *loginTab = new QWidget(tabs_);
    auto *loginLayout = new QFormLayout(loginTab);
    usernameEdit_ = new QLineEdit("user", loginTab);
    passwordEdit_ = new QLineEdit("1234", loginTab);
    passwordEdit_->setEchoMode(QLineEdit::Password);
    auto *loginButton = new QPushButton("Sign in", loginTab);
    loginLayout->addRow("ID", usernameEdit_);
    loginLayout->addRow("Password", passwordEdit_);
    loginLayout->addRow(loginButton);

    auto *productTab = new QWidget(tabs_);
    auto *productLayout = new QVBoxLayout(productTab);
    productList_ = new QListWidget(productTab);
    quantitySpin_ = new QSpinBox(productTab);
    quantitySpin_->setRange(1, 99);
    auto *addCartButton = new QPushButton("Add to cart", productTab);
    productLayout->addWidget(productList_);
    productLayout->addWidget(new QLabel("Quantity", productTab));
    productLayout->addWidget(quantitySpin_);
    productLayout->addWidget(addCartButton);

    auto *cartTab = new QWidget(tabs_);
    auto *cartLayout = new QVBoxLayout(cartTab);
    cartList_ = new QListWidget(cartTab);
    cartTotalLabel_ = new QLabel("Total: 0 KRW", cartTab);
    auto *removeCartButton = new QPushButton("Remove selected item", cartTab);
    auto *clearCartButton = new QPushButton("Clear cart", cartTab);
    addressEdit_ = new QLineEdit(cartTab);
    addressEdit_->setPlaceholderText("Delivery address");
    auto *checkoutButton = new QPushButton("Checkout", cartTab);
    cartLayout->addWidget(cartList_);
    cartLayout->addWidget(cartTotalLabel_);
    cartLayout->addWidget(removeCartButton);
    cartLayout->addWidget(clearCartButton);
    cartLayout->addWidget(addressEdit_);
    cartLayout->addWidget(checkoutButton);

    auto *orderTab = new QWidget(tabs_);
    auto *orderLayout = new QVBoxLayout(orderTab);
    orderList_ = new QListWidget(orderTab);
    orderLayout->addWidget(orderList_);

    auto *reviewTab = new QWidget(tabs_);
    auto *reviewLayout = new QVBoxLayout(reviewTab);
    reviewRatingSpin_ = new QSpinBox(reviewTab);
    reviewRatingSpin_->setRange(1, 5);
    reviewCommentEdit_ = new QLineEdit(reviewTab);
    reviewCommentEdit_->setPlaceholderText("Review comment for selected product");
    auto *reviewButton = new QPushButton("Write review", reviewTab);
    reviewList_ = new QListWidget(reviewTab);
    reviewLayout->addWidget(new QLabel("Select a product in Product tab first", reviewTab));
    reviewLayout->addWidget(reviewRatingSpin_);
    reviewLayout->addWidget(reviewCommentEdit_);
    reviewLayout->addWidget(reviewButton);
    reviewLayout->addWidget(reviewList_);

    tabs_->addTab(loginTab, "Login");
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
        currentUserId_ = user->id();
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
        if (productId == 0 || !cartService_.addProduct(currentUserId_, productId, quantitySpin_->value())) {
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
        cartService_.removeProduct(currentUserId_, cartList_->currentItem()->data(Qt::UserRole).toInt());
        refreshCart();
    });

    connect(clearCartButton, &QPushButton::clicked, this, [this]() {
        if (requireLogin()) {
            cartService_.clear(currentUserId_);
            refreshCart();
        }
    });

    connect(checkoutButton, &QPushButton::clicked, this, [this]() {
        if (!requireLogin()) {
            return;
        }
        const auto order = orderService_.checkout(currentUserId_, Delivery(addressEdit_->text().toStdString()));
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
        reviewService_.addReview(currentUserId_,
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

void MainWindow::refreshProducts()
{
    productList_->clear();
    for (const auto &product : productService_.listProducts()) {
        auto *item = new QListWidgetItem(QString::fromStdString(product.name())
                                         + " | " + QString::fromStdString(categoryToString(product.category()))
                                         + " | " + QString::number(product.price()) + " KRW"
                                         + " | Stock " + QString::number(product.stock()));
        item->setData(Qt::UserRole, product.id());
        productList_->addItem(item);
    }
}

void MainWindow::refreshCart()
{
    cartList_->clear();
    const Cart cart = currentUserId_ == 0 ? Cart() : cartService_.cart(currentUserId_);
    for (const auto &item : cart.items()) {
        auto *row = new QListWidgetItem(QString::fromStdString(item.product().name())
                                        + " x " + QString::number(item.quantity())
                                        + " = " + QString::number(item.totalPrice()) + " KRW");
        row->setData(Qt::UserRole, item.product().id());
        cartList_->addItem(row);
    }
    cartTotalLabel_->setText("Total: " + QString::number(cart.totalPrice()) + " KRW");
}

void MainWindow::refreshOrders()
{
    orderList_->clear();
    if (currentUserId_ == 0) {
        return;
    }

    for (const auto &order : orderService_.ordersForUser(currentUserId_)) {
        orderList_->addItem("Order #" + QString::number(order.id())
                            + " | Total " + QString::number(order.totalPrice()) + " KRW"
                            + " | Address " + QString::fromStdString(order.delivery().address()));
    }
}

void MainWindow::refreshReviews()
{
    reviewList_->clear();
    const int productId = selectedProductId();
    if (productId == 0) {
        return;
    }

    for (const auto &review : reviewService_.reviewsForProduct(productId)) {
        reviewList_->addItem(QString::number(review.rating()) + "/5 | "
                             + QString::fromStdString(review.comment()));
    }
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
    if (currentUserId_ != 0) {
        return true;
    }
    QMessageBox::information(this, "Login required", "Sign in first.");
    tabs_->setCurrentIndex(0);
    return false;
}
