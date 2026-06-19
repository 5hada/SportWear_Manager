#include "receiptPage.h"
#include "ui/common/tableItemUtil.h"

#include <ElaPushButton.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QVBoxLayout>

ReceiptPage::ReceiptPage(QWidget* parent): ElaScrollPage(parent) {
    setWindowTitle("Receipts");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Receipts", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Purchase history.", this);
    descText->setTextPixelSize(16);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ID", "Date", "Items", "Paid", "Point", "Status"});
    centerHeaderItems(model);

    receiptTable = new ElaTableView(this);
    receiptTable->setModel(model);
    receiptTable->setAlternatingRowColors(true);
    receiptTable->verticalHeader()->setHidden(true);
    receiptTable->horizontalHeader()->setStretchLastSection(true);
    receiptTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    receiptTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    receiptTable->setFixedHeight(460);

    connect(receiptTable, &ElaTableView::tableViewShow, this, [this]() {
        receiptTable->setColumnWidth(0, 70);
        receiptTable->setColumnWidth(1, 160);
        receiptTable->setColumnWidth(2, 300);
        receiptTable->setColumnWidth(3, 120);
        receiptTable->setColumnWidth(4, 90);
    });

    auto* refundButton = new ElaPushButton("Refund", this);
    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(refundButton);

    connect(refundButton, &ElaPushButton::clicked, this, [this]() {
        const int receiptId = selectedReceiptId();
        if (receiptId >= 0) {
            Q_EMIT refundRequested(receiptId);
        }
    });

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Receipts");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(12);
    centerLayout->addWidget(receiptTable);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);
}

void ReceiptPage::setReceipts(Receipts receipts, std::vector<std::string> itemSummaries) {
    this->receipts = std::move(receipts);
    this->itemSummaries = std::move(itemSummaries);
    rebuildReceipts();
}

void ReceiptPage::rebuildReceipts() {
    model->removeRows(0, model->rowCount());

    for (int index = 0; index < static_cast<int>(receipts.size()); ++index) {
        const auto& receipt = receipts[index];
        const QString summary = index < static_cast<int>(itemSummaries.size())
            ? QString::fromStdString(itemSummaries[index])
            : "No items";
        QList<QStandardItem*> row;
        row << centeredItem(QString::number(receipt.getId()));
        row << centeredItem(QString::fromStdString(receipt.getDate()));
        row << centeredItem(summary);
        row << centeredItem(QString::number(receipt.getPaid()));
        row << centeredItem(QString::number(receipt.getPoints()));
        row << centeredItem(receipt.getIsCanceled() ? "Canceled" : "Paid");
        model->appendRow(row);
    }
}

int ReceiptPage::selectedReceiptId() const {
    if (receiptTable == nullptr || receiptTable->selectionModel() == nullptr) {
        return -1;
    }

    const auto selectedRows = receiptTable->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        return -1;
    }

    const int row = selectedRows.first().row();
    const auto* receiptIdItem = model->item(row, 0);
    return receiptIdItem == nullptr ? -1 : receiptIdItem->text().toInt();
}
