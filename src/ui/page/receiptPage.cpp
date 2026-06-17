#include "receiptPage.h"

#include <ElaFlowLayout.h>
#include <ElaPopularCard.h>
#include <ElaText.h>
#include <QVBoxLayout>

ReceiptPage::ReceiptPage(QWidget* parent): ElaScrollPage(parent) {
    setWindowTitle("Receipts");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Receipts", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Purchase history.", this);
    descText->setTextPixelSize(16);

    receiptLayout = new ElaFlowLayout(0, 10, 10);
    receiptLayout->setContentsMargins(0, 0, 0, 0);
    receiptLayout->setIsAnimation(true);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Receipts");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(12);
    centerLayout->addLayout(receiptLayout);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);
}

void ReceiptPage::setReceipts(Receipts receipts) {
    this->receipts = std::move(receipts);
    rebuildReceipts();
}

void ReceiptPage::rebuildReceipts() {
    while (auto* item = receiptLayout->takeAt(0)) {
        if (auto* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    for (const auto& receipt : receipts) {
        addReceiptCard(receipt);
    }
}

void ReceiptPage::addReceiptCard(const Receipt& receipt) {
    auto* receiptCard = new ElaPopularCard(this);
    receiptCard->setTitle(QString("Receipt #%1").arg(receipt.getId()));
    receiptCard->setSubTitle(QString("Paid %1 / Point %2").arg(receipt.getPaid()).arg(receipt.getPoints()));
    receiptCard->setInteractiveTips("Detail");
    receiptCard->setDetailedText(QString::fromStdString(receipt.getDate()));
    receiptLayout->addWidget(receiptCard);
}
