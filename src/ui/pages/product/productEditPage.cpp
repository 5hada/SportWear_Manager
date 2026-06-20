#include "productEditPage.h"

#include <ElaComboBox.h>
#include <ElaLineEdit.h>
#include <ElaPlainTextEdit.h>
#include <ElaPushButton.h>
#include <ElaSpinBox.h>
#include <ElaText.h>
#include <QHBoxLayout>
#include <QSignalBlocker>
#include <QVBoxLayout>

ProductEditPage::ProductEditPage(QWidget* parent): ElaScrollPage(parent) {
    initPage();
    initLayout();
    initConnect();
}

void ProductEditPage::initPage() {
    setWindowTitle("Product Edit");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);
}

void ProductEditPage::initLayout() {
    titleText = new ElaText("Add Product", this);
    titleText->setTextPixelSize(35);

    nameEdit = new ElaLineEdit(this);
    nameEdit->setPlaceholderText("Product name");
    nameEdit->setFixedHeight(36);

    categoryCombo = new ElaComboBox(this);
    categoryCombo->setFixedHeight(36);
    for (auto category: Categories) {
        if (category == Category::Unknown) {
            continue;
        }
        categoryCombo->addItem(
            QString::fromStdString(categoryToString(category)),
            QVariant::fromValue(static_cast<int>(category))
        );
    }

    priceSpin = new ElaSpinBox(this);
    priceSpin->setRange(0, 100000000);
    priceSpin->setFixedHeight(36);

    stockSpin = new ElaSpinBox(this);
    stockSpin->setRange(0, 1000000);
    stockSpin->setFixedHeight(36);

    detailEdit = new ElaPlainTextEdit(this);
    detailEdit->setPlaceholderText("Product detail");
    detailEdit->setFixedHeight(120);

    auto* nameLabel = new ElaText("Name", this);
    nameLabel->setTextPixelSize(14);
    auto* categoryLabel = new ElaText("Category", this);
    categoryLabel->setTextPixelSize(14);
    auto* priceLabel = new ElaText("Price", this);
    priceLabel->setTextPixelSize(14);
    auto* stockLabel = new ElaText("Stock", this);
    stockLabel->setTextPixelSize(14);
    auto* detailLabel = new ElaText("Detail", this);
    detailLabel->setTextPixelSize(14);

    auto* priceStockLayout = new QHBoxLayout();
    priceStockLayout->setSpacing(14);
    auto* priceLayout = new QVBoxLayout();
    priceLayout->addWidget(priceLabel);
    priceLayout->addWidget(priceSpin);
    auto* stockLayout = new QVBoxLayout();
    stockLayout->addWidget(stockLabel);
    stockLayout->addWidget(stockSpin);
    priceStockLayout->addLayout(priceLayout);
    priceStockLayout->addLayout(stockLayout);

    auto* saveButton = new ElaPushButton("Save", this);
    saveButton->setFixedSize(120, 36);
    auto* cancelButton = new ElaPushButton("Cancel", this);
    cancelButton->setFixedSize(120, 36);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(saveButton);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Product Edit");
    auto* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(30, 20, 30, 20);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(titleText);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameEdit);
    mainLayout->addWidget(categoryLabel);
    mainLayout->addWidget(categoryCombo);
    mainLayout->addLayout(priceStockLayout);
    mainLayout->addWidget(detailLabel);
    mainLayout->addWidget(detailEdit);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);

    connect(saveButton, &ElaPushButton::clicked, this, [this]() {
        emit saveRequested(
            productId,
            nameEdit->text(),
            selectedCategory(),
            priceSpin->value(),
            stockSpin->value(),
            detailEdit->toPlainText()
        );
    });
    connect(cancelButton, &ElaPushButton::clicked, this, &ProductEditPage::cancelRequested);
}

void ProductEditPage::initConnect() {}

void ProductEditPage::setAddMode() {
    productId = 0;
    titleText->setText("Add Product");
    nameEdit->clear();
    setCategory(Category::Top);
    priceSpin->setValue(0);
    stockSpin->setValue(0);
    detailEdit->clear();
}

void ProductEditPage::setEditMode(const Product& product) {
    productId = product.getId();
    titleText->setText("Edit Product");
    nameEdit->setText(QString::fromStdString(product.getName()));
    setCategory(product.getCategory());
    priceSpin->setValue(product.getPrice());
    stockSpin->setValue(product.getStock());
    detailEdit->setPlainText(QString::fromStdString(product.getDetail()));
}

void ProductEditPage::setCategory(Category category) {
    if (categoryCombo == nullptr) {
        return;
    }
    const QSignalBlocker blocker(categoryCombo);
    for (int i = 0; i < categoryCombo->count(); ++i) {
        if (static_cast<Category>(categoryCombo->itemData(i).toInt()) == category) {
            categoryCombo->setCurrentIndex(i);
            return;
        }
    }
    categoryCombo->setCurrentIndex(0);
}

Category ProductEditPage::selectedCategory() const {
    if (categoryCombo == nullptr || categoryCombo->currentIndex() < 0) {
        return Category::Top;
    }
    return static_cast<Category>(categoryCombo->currentData().toInt());
}
