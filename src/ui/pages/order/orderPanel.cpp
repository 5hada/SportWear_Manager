#include "orderPanel.h"
#include "ui/common/tableItemUtil.h"

#include <ElaPushButton.h>
#include <ElaSpinBox.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
#include <QSignalBlocker>
#include <QStandardItemModel>
#include <QVBoxLayout>


OrderPanel::OrderPanel(QWidget* parent): ElaDialog(parent) {
    setWindowTitle("Order");
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Order", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Review selected cart items before checkout.", this);
    descText->setTextPixelSize(16);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Product ID", "Quantity", "Unit Price", "Total"});
    centerHeaderItems(model);

    orderTable = new ElaTableView(this);
    orderTable->setModel(model);
    orderTable->setAlternatingRowColors(true);
    orderTable->verticalHeader()->setHidden(true);
    orderTable->horizontalHeader()->setStretchLastSection(true);
    orderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    orderTable->setFixedHeight(360);

    totalText = new ElaText("Total: 0", this);
    totalText->setTextPixelSize(18);
    pointText = new ElaText("Available point: 0", this);
    pointText->setTextPixelSize(15);
    pointSpin = new ElaSpinBox(this);
    pointSpin->setRange(0, 0);
    pointSpin->setFixedWidth(150);
    paidText = new ElaText("Payment: 0", this);
    paidText->setTextPixelSize(18);

    auto* confirmButton = new ElaPushButton("Confirm Order", this);
    auto* cancelButton = new ElaPushButton("Cancel", this);

    auto* summaryLayout = new QVBoxLayout();
    summaryLayout->setSpacing(8);
    summaryLayout->addWidget(totalText);
    summaryLayout->addWidget(pointText);
    auto* pointUseLayout = new QHBoxLayout();
    auto* pointUseLabel = new ElaText("Use point", this);
    pointUseLabel->setTextPixelSize(15);
    pointUseLayout->addWidget(pointUseLabel);
    pointUseLayout->addWidget(pointSpin);
    pointUseLayout->addStretch();
    summaryLayout->addLayout(pointUseLayout);
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
        emit confirmRequested(pointSpin->value());
    });
    connect(cancelButton, &ElaPushButton::clicked, this, [this]() {
        emit cancelRequested();
        hide();
    });
    connect(pointSpin, QOverload<int>::of(&ElaSpinBox::valueChanged), this, [this](int usedPoint) {
        Q_EMIT pointChanged(usedPoint);
    });
}

void OrderPanel::setOrder(Order order, int totalPrice, int availablePoints, int maxUsablePoint, int payment) {
    model->removeRows(0, model->rowCount());

    for (const auto& item : order.getItems()) {
        QList<QStandardItem*> row;
        row << centeredItem(QString::number(item.id));
        row << centeredItem(QString::number(item.count));
        row << centeredItem(QString::number(item.price));
        row << centeredItem(QString::number(item.price * item.count));
        model->appendRow(row);
    }

    totalText->setText(QString("Total: %1").arg(totalPrice));
    pointText->setText(QString("Available point: %1").arg(availablePoints));
    const QSignalBlocker blocker(pointSpin);
    pointSpin->setRange(0, maxUsablePoint);
    pointSpin->setValue(0);
    setPayment(payment);
}

void OrderPanel::setPayment(int payment) {
    paidText->setText(QString("Payment: %1").arg(payment));
}
