#include "cartPage.h"
#include "ui/common/tableItemUtil.h"

#include <ElaCheckBox.h>
#include <ElaPushButton.h>
#include <ElaSpinBox.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <algorithm>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QSignalBlocker>
#include <QStandardItemModel>
#include <QTimer>
#include <QVBoxLayout>

namespace {
constexpr int SelectedColumn = 0;
constexpr int ProductIdColumn = 1;
constexpr int QuantityColumn = 2;
constexpr int UnitPriceColumn = 3;
constexpr int TotalColumn = 4;
constexpr int ActionsColumn = 5;
}

CartPage::CartPage(QWidget* parent): ElaScrollPage(parent) {
    setWindowTitle("Cart");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Cart", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Manage products selected for purchase.", this);
    descText->setTextPixelSize(16);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Selected", "Product ID", "Quantity", "Unit Price", "Total", "Actions"});
    centerHeaderItems(model);

    cartTable = new ElaTableView(this);
    cartTable->setModel(model);
    cartTable->setAlternatingRowColors(true);
    cartTable->verticalHeader()->setHidden(true);
    cartTable->horizontalHeader()->setStretchLastSection(true);
    cartTable->setSelectionMode(QAbstractItemView::NoSelection);
    cartTable->setFixedHeight(420);

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
    centerLayout->addWidget(cartTable);
    centerLayout->addLayout(summaryLayout);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);

    connect(clearButton, &ElaPushButton::clicked, this, [this]() {
        cartRequest(CartAction::Clear);
    });

    connect(orderButton, &ElaPushButton::clicked, this, &CartPage::orderRequested);
}

void CartPage::setCart(const Cart& cart) {
    currentCart = cart;
    model->removeRows(0, model->rowCount());

    for (const auto& item : currentCart.getItems()) {
        appendItemRow(item);
    }

    resizeTableColumns();
    refreshSummary();
}

void CartPage::syncCart(const Cart& cart) {
    if (currentCart.getItems().empty() && model->rowCount() == 0) {
        setCart(cart);
        return;
    }

    std::vector<int> removedProductIds;
    for (const auto& currentItem : currentCart.getItems()) {
        const auto found = std::find_if(cart.getItems().begin(), cart.getItems().end(),
                                       [productId = currentItem.id](const CartItem& item) {
                                           return item.id == productId;
                                       });
        if (found == cart.getItems().end()) {
            removedProductIds.push_back(currentItem.id);
        }
    }

    for (const auto& item : cart.getItems()) {
        const int row = findRow(item.id);
        if (row >= 0) {
            updateItemRow(row, item);
        }
        else {
            appendItemRow(item);
        }
    }

    for (int productId : removedProductIds) {
        removeProductRowLater(productId);
    }

    currentCart = cart;
    refreshSummary();
    resizeTableColumns();
}

void CartPage::restoreProductRow(int productId) {
    const auto* item = findItem(productId);
    if (item == nullptr) {
        return;
    }
    updateItemRow(findRow(productId), *item);
    refreshSummary();
}

int CartPage::findRow(int productId) const {
    for (int row = 0; row < model->rowCount(); ++row) {
        const auto* productIdItem = model->item(row, ProductIdColumn);
        if (productIdItem != nullptr && productIdItem->text().toInt() == productId) {
            return row;
        }
    }
    return -1;
}

CartItem* CartPage::findItem(int productId) {
    for (auto& item : currentCart.getItems()) {
        if (item.getId() == productId) {
            return &item;
        }
    }
    return nullptr;
}

void CartPage::appendItemRow(const CartItem& item) {
    QList<QStandardItem*> row;
    row << centeredItem();
    row << centeredItem(QString::number(item.id));
    row << centeredItem();
    row << centeredItem(QString::number(item.price));
    row << centeredItem(QString::number(item.price * item.count));
    row << centeredItem();
    model->appendRow(row);

    const int rowIndex = model->rowCount() - 1;
    auto* selectedCheck = new ElaCheckBox(cartTable);
    selectedCheck->setChecked(item.isSelected());
    connect(selectedCheck, &ElaCheckBox::toggled, this, [this, productId = item.id](bool checked) {
        Q_EMIT cartRequest(CartAction::Toggle, productId, 0, checked);
    });
    auto* selectedCell = new QWidget(cartTable);
    auto* selectedLayout = new QHBoxLayout(selectedCell);
    selectedLayout->setContentsMargins(0, 0, 0, 0);
    selectedLayout->setSpacing(0);
    selectedLayout->addStretch();
    selectedLayout->addWidget(selectedCheck);
    selectedLayout->addStretch();
    cartTable->setIndexWidget(model->index(rowIndex, SelectedColumn), selectedCell);

    auto* quantitySpin = new ElaSpinBox(cartTable);
    quantitySpin->setRange(1, 999);
    quantitySpin->setValue(item.count);
    quantitySpin->setFixedWidth(128);
    connect(quantitySpin, QOverload<int>::of(&ElaSpinBox::valueChanged), this,
            [this, productId = item.id](int value) {
                Q_EMIT cartRequest(CartAction::Set, productId, value);
            });
    auto* quantityCell = new QWidget(cartTable);
    auto* quantityLayout = new QHBoxLayout(quantityCell);
    quantityLayout->setContentsMargins(0, 0, 0, 0);
    quantityLayout->setSpacing(0);
    quantityLayout->addStretch();
    quantityLayout->addWidget(quantitySpin);
    quantityLayout->addStretch();
    cartTable->setIndexWidget(model->index(rowIndex, QuantityColumn), quantityCell);

    auto* decreaseButton = new ElaPushButton("-1", cartTable);
    decreaseButton->setFixedSize(42, 28);
    auto* increaseButton = new ElaPushButton("+1", cartTable);
    increaseButton->setFixedSize(42, 28);
    auto* removeButton = new ElaPushButton("Remove", cartTable);
    removeButton->setFixedSize(82, 28);
    auto* actions = new QWidget(cartTable);
    auto* actionsLayout = new QHBoxLayout(actions);
    actionsLayout->setContentsMargins(0, 0, 0, 0);
    actionsLayout->setSpacing(6);
    actionsLayout->addStretch();
    actionsLayout->addWidget(decreaseButton);
    actionsLayout->addWidget(increaseButton);
    actionsLayout->addWidget(removeButton);
    actionsLayout->addStretch();
    connect(decreaseButton, &ElaPushButton::clicked, this, [this, productId = item.id]() {
        Q_EMIT cartRequest(CartAction::Sub, productId, 1);
    });
    connect(increaseButton, &ElaPushButton::clicked, this, [this, productId = item.id]() {
        Q_EMIT cartRequest(CartAction::Add, productId, 1);
    });
    connect(removeButton, &ElaPushButton::clicked, this, [this, productId = item.id]() {
        Q_EMIT cartRequest(CartAction::Del, productId);
    });
    cartTable->setIndexWidget(model->index(rowIndex, ActionsColumn), actions);
}

void CartPage::updateItemRow(int row, const CartItem& item) {
    if (row < 0) {
        return;
    }

    if (auto* selectedCell = cartTable->indexWidget(model->index(row, SelectedColumn))) {
        if (auto* selectedCheck = selectedCell->findChild<ElaCheckBox*>()) {
            QSignalBlocker blocker(selectedCheck);
            selectedCheck->setChecked(item.isSelected());
        }
    }
    if (auto* quantityCell = cartTable->indexWidget(model->index(row, QuantityColumn))) {
        if (auto* quantitySpin = quantityCell->findChild<ElaSpinBox*>()) {
            QSignalBlocker blocker(quantitySpin);
            quantitySpin->setValue(item.count);
        }
    }

    if (auto* productIdItem = model->item(row, ProductIdColumn)) {
        productIdItem->setText(QString::number(item.id));
    }
    if (auto* priceItem = model->item(row, UnitPriceColumn)) {
        priceItem->setText(QString::number(item.price));
    }
    if (auto* totalItem = model->item(row, TotalColumn)) {
        totalItem->setText(QString::number(item.price * item.count));
    }
}

void CartPage::removeProductRow(int productId) {
    const int row = findRow(productId);
    if (row >= 0) {
        model->removeRow(row);
    }
}

void CartPage::removeProductRowLater(int productId) {
    const int row = findRow(productId);
    if (row >= 0) {
        cartTable->setRowHidden(row, true);
    }
    QTimer::singleShot(0, this, [this, productId]() {
        removeProductRow(productId);
        resizeTableColumns();
    });
}

void CartPage::resizeTableColumns() {
    cartTable->resizeColumnsToContents();
    cartTable->setColumnWidth(SelectedColumn, 86);
    cartTable->setColumnWidth(QuantityColumn, 150);
    cartTable->setColumnWidth(ActionsColumn, 190);
}

void CartPage::refreshSummary() {
    totalCountText->setText(QString("Items: %1").arg(currentCart.getTotalCount()));
    totalPriceText->setText(QString("Total: %1").arg(currentCart.getTotalPrice()));
}
