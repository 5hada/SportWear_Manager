#include "orderPage.h"

#include <QLabel>
#include <QVBoxLayout>

OrderPage::OrderPage(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Orders", this));
    setLayout(layout);
}

void OrderPage::buildInterface(){
    auto *orderTab = new QWidget(tab);
    auto *orderLayout = new QVBoxLayout(orderTab);
    orderList = new QListWidget(orderTab);
    orderLayout->addWidget(orderList);
}

void OrderPage::refreshOrders() {
    orderList->clear();
    if (app.currentUserId == 0) {
        return;
    }

    for (const auto &order : app.services.order.ordersForUser(app.currentUserId)) {
        orderList->addItem("Order #" + QString::number(order.id())
                            + " | Total " + QString::number(order.totalPrice()) + " KRW"
                            + " | Address " + QString::fromStdString(order.delivery().address()));
    }
}
