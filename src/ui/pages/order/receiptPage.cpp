#include "receiptPage.h"
#include "ui/common/tableItemUtil.h"

#include <ElaIconButton.h>
#include <ElaPushButton.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <initializer_list>

namespace {
constexpr int FixedRowCount = 8;
constexpr int HeaderHeight = 36;
constexpr int RowHeight = 42;
constexpr int ActionColumn = 5;

QWidget* centeredWidget(QWidget* child, QWidget* parent) {
    auto* container = new QWidget(parent);
    auto* layout = new QHBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(6);
    layout->addStretch();
    layout->addWidget(child);
    layout->addStretch();
    return container;
}

void applyColumnWidths(ElaTableView* table, std::initializer_list<int> widths) {
    int column = 0;
    int totalWidth = table->frameWidth() * 2 + 2;
    for (int width : widths) {
        table->horizontalHeader()->resizeSection(column, width);
        totalWidth += width;
        ++column;
    }
    table->setFixedWidth(totalWidth);
}

void applyFixedTableLayout(ElaTableView* table, std::initializer_list<int> widths) {
    table->horizontalHeader()->setStretchLastSection(false);
    table->horizontalHeader()->setMinimumSectionSize(1);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setDefaultSectionSize(RowHeight);
    table->verticalHeader()->setMinimumSectionSize(RowHeight);
    table->horizontalHeader()->setFixedHeight(HeaderHeight);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setFixedHeight(HeaderHeight + (FixedRowCount * RowHeight) + (table->frameWidth() * 2) + 2);
    applyColumnWidths(table, widths);
}
}

ReceiptPage::ReceiptPage(QWidget* parent): ElaScrollPage(parent) {
    setWindowTitle("Receipts");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Receipts", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Purchase history.", this);
    descText->setTextPixelSize(16);

    model = new QStandardItemModel(FixedRowCount, 6, this);
    model->setHorizontalHeaderLabels({"ID", "Date", "Items", "Paid", "Status", "Actions"});
    centerHeaderItems(model);
    for (int row = 0; row < FixedRowCount; ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            model->setItem(row, column, centeredItem());
        }
    }

    receiptTable = new ElaTableView(this);
    receiptTable->setModel(model);
    receiptTable->setAlternatingRowColors(true);
    receiptTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    receiptTable->setSelectionMode(QAbstractItemView::NoSelection);
    receiptTable->setTextElideMode(Qt::ElideRight);
    receiptTable->verticalHeader()->setVisible(false);
    applyFixedTableLayout(receiptTable, {50, 160, 300, 120, 70, 100});
    connect(receiptTable, &ElaTableView::tableViewShow, this, [this]() {
        applyColumnWidths(receiptTable, {50, 160, 300, 120, 70, 100});
    });
    rows.reserve(FixedRowCount);
    for (int row = 0; row < FixedRowCount; ++row) {
        auto* refundButton = new ElaPushButton("Refund", receiptTable);
        refundButton->setFixedSize(82, 28);
        auto* cell = centeredWidget(refundButton, receiptTable);
        cell->hide();
        receiptTable->setIndexWidget(model->index(row, ActionColumn), cell);
        refundButton->hide();
        rows.push_back({cell, refundButton, -1});

        connect(refundButton, &ElaPushButton::clicked, this, [this, row]() {
            if (rows[row].receiptId > 0) {
                Q_EMIT refundRequested(rows[row].receiptId);
            }
        });
    }

    previousButton = new ElaIconButton(ElaIconType::AngleLeft, this);
    previousButton->setFixedSize(30, 30);
    pageText = new ElaText("1 / 1", this);
    pageText->setFixedSize(70, 30);
    pageText->setAlignment(Qt::AlignCenter);
    pageText->setTextPixelSize(12);
    nextButton = new ElaIconButton(ElaIconType::AngleRight, this);
    nextButton->setFixedSize(30, 30);

    auto* navigationLayout = new QHBoxLayout();
    navigationLayout->setContentsMargins(0, 0, 0, 0);
    navigationLayout->addStretch();
    navigationLayout->addWidget(previousButton);
    navigationLayout->addWidget(pageText);
    navigationLayout->addWidget(nextButton);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Receipts");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(12);
    centerLayout->addLayout(navigationLayout);
    centerLayout->addWidget(receiptTable);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);

    connect(previousButton, &ElaIconButton::clicked, this, [this]() {
        Q_EMIT pageMoveRequested(-1);
    });
    connect(nextButton, &ElaIconButton::clicked, this, [this]() {
        Q_EMIT pageMoveRequested(1);
    });
}

void ReceiptPage::clearRow(int row) {
    for (int column = 0; column < model->columnCount(); ++column) {
        model->item(row, column)->setText("");
    }
    rows[row].receiptId = -1;
    rows[row].refundCell->hide();
    rows[row].refundButton->hide();
}

void ReceiptPage::setPageInfo(int currentPage, int maxPage) {
    const int normalizedMax = maxPage < 0 ? 0 : maxPage;
    const int normalizedCurrent = currentPage < 0 ? 0 : currentPage;
    pageText->setText(QString("%1 / %2").arg(normalizedCurrent + 1).arg(normalizedMax + 1));
    previousButton->setEnabled(normalizedCurrent > 0);
    nextButton->setEnabled(normalizedCurrent < normalizedMax);
}

void ReceiptPage::refreshContent(const ReceiptPageContent& content) {
    setPageInfo(content.currentPage, content.maxPage);
    for (int row = 0; row < FixedRowCount; ++row) {
        clearRow(row);
    }

    for (int row = 0; row < static_cast<int>(content.receipts.size()); ++row) {
        if (row >= FixedRowCount) {
            break;
        }
        const auto& receipt = content.receipts[row];
        const QString summary = row < static_cast<int>(content.itemSummaries.size())
            ? QString::fromStdString(content.itemSummaries[row])
            : "No items";
        const bool refundable = row < static_cast<int>(content.refundable.size()) && content.refundable[row];

        model->item(row, 0)->setText(QString::number(receipt.getId()));
        model->item(row, 1)->setText(QString::fromStdString(receipt.getDate()));
        model->item(row, 2)->setText(summary);
        model->item(row, 3)->setText(QString::number(receipt.getPaid()));
        model->item(row, 4)->setText(receipt.getIsCanceled() ? "Canceled" : "Paid");

        rows[row].receiptId = refundable ? receipt.getId() : -1;
        if (refundable) {
            rows[row].refundCell->show();
            rows[row].refundButton->show();
        }
    }
}
