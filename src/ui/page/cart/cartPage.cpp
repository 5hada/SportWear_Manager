#include "cartPage.h"

#include <ElaPushButton.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QVBoxLayout>

CartPage::CartPage(QWidget* parent): ElaScrollPage(parent) {
    setWindowTitle("Cart");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Cart", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Manage products selected for purchase.", this);
    descText->setTextPixelSize(16);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Selected", "Product ID", "Quantity", "Unit Price", "Total"});

    cartTable = new ElaTableView(this);
    cartTable->setModel(model);
    cartTable->setAlternatingRowColors(true);
    cartTable->verticalHeader()->setHidden(true);
    cartTable->horizontalHeader()->setStretchLastSection(true);
    cartTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    cartTable->setFixedHeight(420);

    totalCountText = new ElaText("Items: 0", this);
    totalCountText->setTextPixelSize(16);
    totalPriceText = new ElaText("Total: 0", this);
    totalPriceText->setTextPixelSize(18);

    auto* removeButton = new ElaPushButton("Remove", this);
    auto* decreaseButton = new ElaPushButton("-1", this);
    auto* increaseButton = new ElaPushButton("+1", this);
    auto* toggleButton = new ElaPushButton("Toggle", this);
    auto* clearButton = new ElaPushButton("Clear", this);
    auto* orderButton = new ElaPushButton("Order", this);

    auto* summaryLayout = new QHBoxLayout();
    summaryLayout->addWidget(totalCountText);
    summaryLayout->addSpacing(20);
    summaryLayout->addWidget(totalPriceText);
    summaryLayout->addStretch();

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(decreaseButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(increaseButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(toggleButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(orderButton);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Cart");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(12);
    centerLayout->addWidget(cartTable);
    centerLayout->addLayout(summaryLayout);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);

    connect(decreaseButton, &ElaPushButton::clicked, this, [this]() {
        const int productId = selectedProductId();
        if (productId >= 0) {
            Q_EMIT decreaseRequested(productId);
        }
    });
    connect(increaseButton, &ElaPushButton::clicked, this, [this]() {
        const int productId = selectedProductId();
        if (productId >= 0) {
            Q_EMIT increaseRequested(productId);
        }
    });
    connect(toggleButton, &ElaPushButton::clicked, this, [this]() {
        const int productId = selectedProductId();
        if (productId >= 0) {
            Q_EMIT toggleSelectedRequested(productId, !selectedProductIsSelected());
        }
    });
    connect(removeButton, &ElaPushButton::clicked, this, [this]() {
        const int productId = selectedProductId();
        if (productId >= 0) {
            Q_EMIT removeRequested(productId);
        }
    });
    connect(clearButton, &ElaPushButton::clicked, this, &CartPage::clearRequested);
    connect(orderButton, &ElaPushButton::clicked, this, &CartPage::orderRequested);
}

void CartPage::setCart(const Cart& cart) {
    model->removeRows(0, model->rowCount());

    for (const auto& item : cart.getItems()) {
        QList<QStandardItem*> row;
        row << new QStandardItem(item.isSelected ? "Yes" : "No");
        row << new QStandardItem(QString::number(item.id));
        row << new QStandardItem(QString::number(item.count));
        row << new QStandardItem(QString::number(item.price));
        row << new QStandardItem(QString::number(item.price * item.count));
        model->appendRow(row);
    }

    totalCountText->setText(QString("Items: %1").arg(cart.getTotalCount()));
    totalPriceText->setText(QString("Total: %1").arg(cart.getTotalPrice()));
}

int CartPage::selectedProductId() const {
    if (cartTable == nullptr || cartTable->selectionModel() == nullptr) {
        return -1;
    }

    const auto selectedRows = cartTable->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        return -1;
    }

    const int row = selectedRows.first().row();
    const auto* productIdItem = model->item(row, 1);
    return productIdItem == nullptr ? -1 : productIdItem->text().toInt();
}

bool CartPage::selectedProductIsSelected() const {
    if (cartTable == nullptr || cartTable->selectionModel() == nullptr) {
        return false;
    }

    const auto selectedRows = cartTable->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        return false;
    }

    const int row = selectedRows.first().row();
    const auto* selectedItem = model->item(row, 0);
    return selectedItem != nullptr && selectedItem->text() == "Yes";
}
