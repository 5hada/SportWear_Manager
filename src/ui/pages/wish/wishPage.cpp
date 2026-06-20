#include "wishPage.h"
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
constexpr int ActionColumn = 3;

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

WishPage::WishPage(QWidget* parent): ElaScrollPage(parent) {
    setWindowTitle("Wish List");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Wish List", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Products saved for later purchase.", this);
    descText->setTextPixelSize(16);

    model = new QStandardItemModel(FixedRowCount, 4, this);
    model->setHorizontalHeaderLabels({"Name", "Price", "Stock", "Actions"});
    centerHeaderItems(model);
    for (int row = 0; row < FixedRowCount; ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            model->setItem(row, column, centeredItem());
        }
    }

    wishTable = new ElaTableView(this);
    wishTable->setModel(model);
    wishTable->setAlternatingRowColors(true);
    wishTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    wishTable->setSelectionMode(QAbstractItemView::NoSelection);
    wishTable->setTextElideMode(Qt::ElideRight);
    wishTable->verticalHeader()->setVisible(false);
    applyFixedTableLayout(wishTable, {320, 120, 100, 190});
    connect(wishTable, &ElaTableView::tableViewShow, this, [this]() {
        applyColumnWidths(wishTable, {320, 120, 100, 190});
    });
    rows.reserve(FixedRowCount);
    for (int row = 0; row < FixedRowCount; ++row) {
        auto* actions = new QWidget(wishTable);
        auto* actionsLayout = new QHBoxLayout(actions);
        actionsLayout->setContentsMargins(0, 0, 0, 0);
        actionsLayout->setSpacing(6);
        auto* cartButton = new ElaPushButton("장바구니 추가", actions);
        cartButton->setFixedSize(96, 28);
        auto* removeButton = new ElaPushButton("위시 삭제", actions);
        removeButton->setFixedSize(86, 28);
        actionsLayout->addWidget(cartButton);
        actionsLayout->addWidget(removeButton);

        auto* cell = centeredWidget(actions, wishTable);
        cell->hide();
        wishTable->setIndexWidget(model->index(row, ActionColumn), cell);
        cartButton->hide();
        removeButton->hide();
        rows.push_back({cell, cartButton, removeButton, -1});

        connect(cartButton, &ElaPushButton::clicked, this, [this, row]() {
            if (rows[row].productId > 0) {
                Q_EMIT cartRequested(rows[row].productId);
            }
        });
        connect(removeButton, &ElaPushButton::clicked, this, [this, row]() {
            if (rows[row].productId > 0) {
                Q_EMIT removeRequested(rows[row].productId);
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
    centralWidget->setWindowTitle("Wish List");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(12);
    centerLayout->addLayout(navigationLayout);
    centerLayout->addWidget(wishTable);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);

    connect(previousButton, &ElaIconButton::clicked, this, [this]() {
        Q_EMIT pageMoveRequested(-1);
    });
    connect(nextButton, &ElaIconButton::clicked, this, [this]() {
        Q_EMIT pageMoveRequested(1);
    });
}

void WishPage::clearRow(int row) {
    for (int column = 0; column < model->columnCount(); ++column) {
        model->item(row, column)->setText("");
    }
    rows[row].productId = -1;
    rows[row].actions->hide();
    rows[row].cartButton->hide();
    rows[row].removeButton->hide();
}

void WishPage::setPageInfo(int currentPage, int maxPage) {
    const int normalizedMax = maxPage < 0 ? 0 : maxPage;
    const int normalizedCurrent = currentPage < 0 ? 0 : currentPage;
    pageText->setText(QString("%1 / %2").arg(normalizedCurrent + 1).arg(normalizedMax + 1));
    previousButton->setEnabled(normalizedCurrent > 0);
    nextButton->setEnabled(normalizedCurrent < normalizedMax);
}

void WishPage::refreshContent(const WishPageContent& content) {
    setPageInfo(content.currentPage, content.maxPage);
    for (int row = 0; row < FixedRowCount; ++row) {
        clearRow(row);
    }

    int row = 0;
    for (const auto& product : content.products) {
        if (row >= FixedRowCount) {
            break;
        }
        model->item(row, 0)->setText(product.getName().empty() ? "Sample Product" : QString::fromStdString(product.getName()));
        model->item(row, 1)->setText(QString::number(product.getPrice()));
        model->item(row, 2)->setText(QString::number(product.getStock()));
        rows[row].productId = product.getId();
        rows[row].actions->show();
        rows[row].cartButton->show();
        rows[row].removeButton->show();
        ++row;
    }
}
