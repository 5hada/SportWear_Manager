#include "cartPage.h"
#include "ui/common/tableItemUtil.h"

#include <ElaCheckBox.h>
#include <ElaIconButton.h>
#include <ElaPushButton.h>
#include <ElaSpinBox.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QSignalBlocker>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <initializer_list>

namespace {
constexpr int FixedRowCount = 8;
constexpr int HeaderHeight = 36;
constexpr int RowHeight = 42;
constexpr int SelectedColumn = 0;
constexpr int QuantityColumn = 2;
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

CartPage::CartPage(QWidget* parent): ElaScrollPage(parent) {
    setWindowTitle("Cart");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Cart", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Manage products selected for purchase.", this);
    descText->setTextPixelSize(16);

    model = new QStandardItemModel(FixedRowCount, 6, this);
    model->setHorizontalHeaderLabels({"Select", "Name", "Count", "Unit Price", "Total", "Actions"});
    centerHeaderItems(model);
    for (int row = 0; row < FixedRowCount; ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            model->setItem(row, column, centeredItem());
        }
    }

    cartTable = new ElaTableView(this);
    cartTable->setModel(model);
    cartTable->setAlternatingRowColors(true);
    cartTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cartTable->setSelectionMode(QAbstractItemView::NoSelection);
    cartTable->setTextElideMode(Qt::ElideRight);
    cartTable->verticalHeader()->setVisible(false);
    applyFixedTableLayout(cartTable, {60, 250, 120, 100, 100, 190});
    connect(cartTable, &ElaTableView::tableViewShow, this, [this]() {
        applyColumnWidths(cartTable, {60, 250, 120, 100, 100, 190});
    });
    rows.reserve(FixedRowCount);
    for (int row = 0; row < FixedRowCount; ++row) {
        auto* selectedCheck = new ElaCheckBox(cartTable);
        auto* selectedCell = centeredWidget(selectedCheck, cartTable);
        selectedCell->hide();
        cartTable->setIndexWidget(model->index(row, SelectedColumn), selectedCell);
        selectedCheck->hide();

        auto* quantitySpin = new ElaSpinBox(cartTable);
        quantitySpin->setRange(1, 999);
        quantitySpin->setFixedWidth(112);
        auto* quantityCell = centeredWidget(quantitySpin, cartTable);
        quantityCell->hide();
        cartTable->setIndexWidget(model->index(row, QuantityColumn), quantityCell);
        quantitySpin->hide();

        auto* actions = new QWidget(cartTable);
        auto* actionsLayout = new QHBoxLayout(actions);
        actionsLayout->setContentsMargins(0, 0, 0, 0);
        actionsLayout->setSpacing(6);
        auto* decreaseButton = new ElaPushButton("-1", actions);
        decreaseButton->setFixedSize(42, 28);
        auto* increaseButton = new ElaPushButton("+1", actions);
        increaseButton->setFixedSize(42, 28);
        auto* removeButton = new ElaPushButton("Remove", actions);
        removeButton->setFixedSize(82, 28);
        actionsLayout->addWidget(decreaseButton);
        actionsLayout->addWidget(increaseButton);
        actionsLayout->addWidget(removeButton);
        auto* actionCell = centeredWidget(actions, cartTable);
        actionCell->hide();
        cartTable->setIndexWidget(model->index(row, ActionColumn), actionCell);
        decreaseButton->hide();
        increaseButton->hide();
        removeButton->hide();

        rows.push_back({
            selectedCell,
            selectedCheck,
            quantityCell,
            quantitySpin,
            actionCell,
            decreaseButton,
            increaseButton,
            removeButton,
            -1
        });

        connect(selectedCheck, &ElaCheckBox::clicked, this, [this, row](bool checked) {
            if (rows[row].productId > 0) {
                Q_EMIT cartRequest(CartAction::Toggle, rows[row].productId, 0, checked);
            }
        });
        connect(quantitySpin, QOverload<int>::of(&ElaSpinBox::valueChanged), this, [this, row](int value) {
            if (rows[row].productId > 0 && rows[row].quantityCell->isVisible()) {
                Q_EMIT cartRequest(CartAction::Set, rows[row].productId, value);
            }
        });
        connect(decreaseButton, &ElaPushButton::clicked, this, [this, row]() {
            if (rows[row].productId > 0) {
                Q_EMIT cartRequest(CartAction::Sub, rows[row].productId, 1);
            }
        });
        connect(increaseButton, &ElaPushButton::clicked, this, [this, row]() {
            if (rows[row].productId > 0) {
                Q_EMIT cartRequest(CartAction::Add, rows[row].productId, 1);
            }
        });
        connect(removeButton, &ElaPushButton::clicked, this, [this, row]() {
            if (rows[row].productId > 0) {
                Q_EMIT cartRequest(CartAction::Del, rows[row].productId);
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

    totalCountText = new ElaText("Items: 0", this);
    totalCountText->setTextPixelSize(16);
    totalPriceText = new ElaText("Total: 0", this);
    totalPriceText->setTextPixelSize(18);

    auto* clearButton = new ElaPushButton("Clear", this);
    auto* orderButton = new ElaPushButton("Order", this);

    auto* summaryLayout = new QHBoxLayout();
    summaryLayout->addWidget(totalCountText);
    summaryLayout->addSpacing(20);
    summaryLayout->addWidget(totalPriceText);
    summaryLayout->addStretch();

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
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
    centerLayout->addLayout(navigationLayout);
    centerLayout->addWidget(cartTable);
    centerLayout->addLayout(summaryLayout);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);

    connect(clearButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT cartRequest(CartAction::Clear);
    });
    connect(orderButton, &ElaPushButton::clicked, this, &CartPage::orderRequested);
    connect(previousButton, &ElaIconButton::clicked, this, [this]() {
        Q_EMIT pageMoveRequested(-1);
    });
    connect(nextButton, &ElaIconButton::clicked, this, [this]() {
        Q_EMIT pageMoveRequested(1);
    });
}

void CartPage::clearRow(int row) {
    for (int column = 0; column < model->columnCount(); ++column) {
        model->item(row, column)->setText("");
    }
    rows[row].productId = -1;
    rows[row].selectedCell->hide();
    rows[row].selectedCheck->hide();
    rows[row].quantityCell->hide();
    rows[row].quantitySpin->hide();
    rows[row].actions->hide();
    rows[row].decreaseButton->hide();
    rows[row].increaseButton->hide();
    rows[row].removeButton->hide();
}

void CartPage::setPageInfo(int currentPage, int maxPage) {
    const int normalizedMax = maxPage < 0 ? 0 : maxPage;
    const int normalizedCurrent = currentPage < 0 ? 0 : currentPage;
    pageText->setText(QString("%1 / %2").arg(normalizedCurrent + 1).arg(normalizedMax + 1));
    previousButton->setEnabled(normalizedCurrent > 0);
    nextButton->setEnabled(normalizedCurrent < normalizedMax);
}

void CartPage::refreshContent(const CartPageContent& content) {
    setPageInfo(content.currentPage, content.maxPage);
    for (int row = 0; row < FixedRowCount; ++row) {
        clearRow(row);
    }

    int row = 0;
    for (const auto& item : content.cart.getItems()) {
        if (row >= FixedRowCount) {
            break;
        }
        const int itemTotal = row < static_cast<int>(content.itemTotals.size()) ? content.itemTotals[row] : 0;
        const QString productName = row < static_cast<int>(content.productNames.size())
            ? QString::fromStdString(content.productNames[row])
            : QString("Unknown");
        {
            const QSignalBlocker blocker(rows[row].selectedCheck);
            rows[row].selectedCheck->setChecked(item.isSelected());
        }
        {
            const QSignalBlocker blocker(rows[row].quantitySpin);
            rows[row].quantitySpin->setValue(item.count);
        }

        rows[row].productId = item.id;
        rows[row].selectedCell->show();
        rows[row].selectedCheck->show();
        model->item(row, 1)->setText(productName);
        rows[row].quantityCell->show();
        rows[row].quantitySpin->show();
        model->item(row, 3)->setText(QString::number(item.price));
        model->item(row, 4)->setText(QString::number(itemTotal));
        rows[row].actions->show();
        rows[row].decreaseButton->show();
        rows[row].increaseButton->show();
        rows[row].removeButton->show();
        ++row;
    }

    totalCountText->setText(QString("Items: %1").arg(content.totalCount));
    totalPriceText->setText(QString("Total: %1").arg(content.totalPrice));
}
