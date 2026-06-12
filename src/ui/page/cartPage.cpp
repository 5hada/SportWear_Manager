#include "cartPage.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

CartPage::CartPage(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Cart", this));
    setLayout(layout);
}

void CartPage::buildInterface() {
    auto *cartTab = new QWidget(tab);
    auto *cartLayout = new QVBoxLayout(cartTab);
    cartList = new QListWidget(cartTab);
    cartTotalLabel = new QLabel("Total: 0 KRW", cartTab);
    auto *removeCartButton = new QPushButton("Remove selected item", cartTab);
    auto *clearCartButton = new QPushButton("Clear cart", cartTab);
    addressEdit = new QLineEdit(cartTab);
    addressEdit->setPlaceholderText("Delivery address");
    auto *checkoutButton = new QPushButton("Checkout", cartTab);

    cartLayout->addWidget(cartList);
    cartLayout->addWidget(cartTotalLabel);
    cartLayout->addWidget(removeCartButton);
    cartLayout->addWidget(clearCartButton);
    cartLayout->addWidget(addressEdit);
    cartLayout->addWidget(checkoutButton);
}

void CartPage::refreshCart() {
    cartList->clear();
    const Cart cart = app.currentUserId == 0 ? Cart() : app.services.cart.cart(app.currentUserId);
    for (const auto &item : cart.items()) {
        auto *row = new QListWidgetItem(QString::fromStdString(item.product().name())
                                        + " x " + QString::number(item.quantity())
                                        + " = " + QString::number(item.totalPrice()) + " KRW");
        row->setData(Qt::UserRole, item.product().id());
        cartList->addItem(row);
    }
    cartTotalLabel->setText("Total: " + QString::number(cart.totalPrice()) + " KRW");
}