#include "wishPage.h"

#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QVBoxLayout>

WishPage::WishPage(QWidget* parent)
    : ElaScrollPage(parent)
{
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

WishPage::~WishPage() = default;

void WishPage::setWishProducts(std::vector<Product> products)
{
    wishProducts = std::move(products);
    rebuildRows();
}

void WishPage::rebuildRows()
{
    model->removeRows(0, model->rowCount());

    for (const auto& product : wishProducts) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(product.getId()));
        row << new QStandardItem(product.getName().empty() ? "Sample Product" : QString::fromStdString(product.getName()));
        row << new QStandardItem(QString::number(product.getPrice()));
        row << new QStandardItem(QString::number(product.getStock()));
        model->appendRow(row);
    }
}
