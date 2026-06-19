#include "wishPage.h"
#include "ui/common/tableItemUtil.h"

#include <ElaPushButton.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
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
    model->setHorizontalHeaderLabels({"ID", "Name", "Price", "Stock", "Actions"});
    centerHeaderItems(model);

    wishTable = new ElaTableView(this);
    wishTable->setModel(model);
    wishTable->setAlternatingRowColors(true);
    wishTable->verticalHeader()->setHidden(true);
    wishTable->horizontalHeader()->setStretchLastSection(true);
    wishTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    wishTable->setSelectionMode(QAbstractItemView::NoSelection);
    wishTable->setFixedHeight(450);

    connect(wishTable, &ElaTableView::tableViewShow, this, [this]() {
        wishTable->setColumnWidth(0, 70);
        wishTable->setColumnWidth(1, 260);
        wishTable->setColumnWidth(2, 120);
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

    int rowIndex = 0;
    for (const auto& product : wishs) {
        QList<QStandardItem*> row;
        row << centeredItem(QString::number(product.getId()));
        row << centeredItem(product.getName().empty() ? "Sample Product" : QString::fromStdString(product.getName()));
        row << centeredItem(QString::number(product.getPrice()));
        row << centeredItem(QString::number(product.getStock()));
        row << centeredItem();
        model->appendRow(row);

        auto* cartButton = new ElaPushButton("Add Cart", wishTable);
        cartButton->setFixedSize(88, 28);
        auto* removeButton = new ElaPushButton("Remove", wishTable);
        removeButton->setFixedSize(82, 28);
        auto* actions = new QWidget(wishTable);
        auto* actionsLayout = new QHBoxLayout(actions);
        actionsLayout->setContentsMargins(0, 0, 0, 0);
        actionsLayout->setSpacing(6);
        actionsLayout->addStretch();
        actionsLayout->addWidget(cartButton);
        actionsLayout->addWidget(removeButton);
        actionsLayout->addStretch();
        connect(cartButton, &ElaPushButton::clicked, this, [this, productId = product.getId()]() {
            Q_EMIT cartRequested(productId);
        });
        connect(removeButton, &ElaPushButton::clicked, this, [this, productId = product.getId()]() {
            Q_EMIT removeRequested(productId);
        });
        wishTable->setIndexWidget(model->index(rowIndex, 4), actions);
        ++rowIndex;
    }
    wishTable->resizeColumnsToContents();
    wishTable->setColumnWidth(1, 260);
    wishTable->setColumnWidth(4, 190);
}
