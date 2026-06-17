#include "orderPanel.h"

#include <ElaPushButton.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <tuple>

OrderPanel::OrderPanel(QWidget* parent): ElaDialog(parent) {
    setWindowTitle("Order");
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Order", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Review selected cart items before checkout.", this);
    descText->setTextPixelSize(16);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Product ID", "Quantity", "Unit Price", "Total"});

    orderTable = new ElaTableView(this);
    orderTable->setModel(model);
    orderTable->setAlternatingRowColors(true);
    orderTable->verticalHeader()->setHidden(true);
    orderTable->horizontalHeader()->setStretchLastSection(true);
    orderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    orderTable->setFixedHeight(360);

    totalText = new ElaText("Total: 0", this);
    totalText->setTextPixelSize(18);
    pointText = new ElaText("Point to use: 0", this);
    pointText->setTextPixelSize(15);
    paidText = new ElaText("Payment: 0", this);
    paidText->setTextPixelSize(18);

    auto* confirmButton = new ElaPushButton("Confirm Order", this);
    auto* cancelButton = new ElaPushButton("Cancel", this);

    auto* summaryLayout = new QVBoxLayout();
    summaryLayout->setSpacing(8);
    summaryLayout->addWidget(totalText);
    summaryLayout->addWidget(pointText);
    summaryLayout->addWidget(paidText);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(confirmButton);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Order");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(12);
    centerLayout->addWidget(orderTable);
    centerLayout->addLayout(summaryLayout);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addStretch();

    setLayout(centerLayout);

    connect(confirmButton, &ElaPushButton::clicked, this, [this]() {
        emit confirmRequested(0);
    });
    connect(cancelButton, &ElaPushButton::clicked, this, [this]() {
        emit cancelRequested();
        close();
    });
}

void OrderPanel::setOrder(const std::tuple<Order&, int> orderData) {
    Order& order = std::get<0>(orderData);
    int availablePoint = std::get<1>(orderData);
    moveToCenter();
    show();
    model->removeRows(0, model->rowCount());

    for (const auto& item : order.getItems()) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(item.id));
        row << new QStandardItem(QString::number(item.count));
        row << new QStandardItem(QString::number(item.price));
        row << new QStandardItem(QString::number(item.price * item.count));
        model->appendRow(row);
    }

    totalText->setText(QString("Total: %1").arg(order.getTotalPrice()));
    pointText->setText(QString("Available point: %1").arg(availablePoint));
    paidText->setText(QString("Payment: %1").arg(order.getTotalPrice()));
}
