#include "cartPage.h"

#include <ElaPushButton.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
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
    auto* clearButton = new ElaPushButton("Clear", this);
    auto* orderButton = new ElaPushButton("Order", this);

    auto* summaryLayout = new QHBoxLayout();
    summaryLayout->addWidget(totalCountText);
    summaryLayout->addSpacing(20);
    summaryLayout->addWidget(totalPriceText);
    summaryLayout->addStretch();

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
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
}
