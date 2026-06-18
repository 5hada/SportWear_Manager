#include "wishPage.h"

#include <ElaPushButton.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QVBoxLayout>

WishPage::WishPage(QWidget* parent): ElaScrollPage(parent) {
    setWindowTitle("Wish List");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Wish List", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Products saved for later purchase.", this);
    descText->setTextPixelSize(16);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ID", "Name", "Price", "Stock"});

    wishTable = new ElaTableView(this);
    wishTable->setModel(model);
    wishTable->setAlternatingRowColors(true);
    wishTable->verticalHeader()->setHidden(true);
    wishTable->horizontalHeader()->setStretchLastSection(true);
    wishTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    wishTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    wishTable->setFixedHeight(450);

    connect(wishTable, &ElaTableView::tableViewShow, this, [this]() {
        wishTable->setColumnWidth(0, 70);
        wishTable->setColumnWidth(1, 260);
        wishTable->setColumnWidth(2, 120);
    });
    connect(wishTable, &ElaTableView::doubleClicked, this, [this]() {
        const int productId = selectedProductId();
        if (productId >= 0) {
            Q_EMIT productSelected(productId);
        }
    });

    auto* openButton = new ElaPushButton("Open", this);
    auto* removeButton = new ElaPushButton("Remove", this);
    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(openButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(removeButton);

    connect(openButton, &ElaPushButton::clicked, this, [this]() {
        const int productId = selectedProductId();
        if (productId >= 0) {
            Q_EMIT productSelected(productId);
        }
    });
    connect(removeButton, &ElaPushButton::clicked, this, [this]() {
        const int productId = selectedProductId();
        if (productId >= 0) {
            Q_EMIT removeRequested(productId);
        }
    });

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Wish List");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(12);
    centerLayout->addWidget(wishTable);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);
    rebuildRows();
}

void WishPage::setWishs(Products wishs) {
    this->wishs = std::move(wishs);
    rebuildRows();
}

void WishPage::rebuildRows() {
    model->removeRows(0, model->rowCount());

    for (const auto& product : wishs) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(product.getId()));
        row << new QStandardItem(product.getName().empty() ? "Sample Product" : QString::fromStdString(product.getName()));
        row << new QStandardItem(QString::number(product.getPrice()));
        row << new QStandardItem(QString::number(product.getStock()));
        model->appendRow(row);
    }
}

int WishPage::selectedProductId() const {
    if (wishTable == nullptr || wishTable->selectionModel() == nullptr) {
        return -1;
    }

    const auto selectedRows = wishTable->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        return -1;
    }

    const int row = selectedRows.first().row();
    const auto* productIdItem = model->item(row, 0);
    return productIdItem == nullptr ? -1 : productIdItem->text().toInt();
}
