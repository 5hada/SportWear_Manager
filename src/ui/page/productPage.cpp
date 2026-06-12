#include "productPage.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>

ProductPage::ProductPage(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Product List", this));
    setLayout(layout);
}

void ProductPage::buildInterface() {
    auto *productTab = new QWidget(tab);
    auto *productLayout = new QVBoxLayout(productTab);
    productList = new QListWidget(productTab);
    quantitySpin = new QSpinBox(productTab);
    quantitySpin->setRange(1, 99);
    auto *addCartButton = new QPushButton("Add to cart", productTab);
    productLayout->addWidget(productList);
    productLayout->addWidget(new QLabel("Quantity", productTab));
    productLayout->addWidget(quantitySpin);
    productLayout->addWidget(addCartButton);
}

void ProductPage::refreshProducts() {
    productList->clear();
    for (const auto &product : app.services.product.listProducts()) {
        auto *item = new QListWidgetItem(QString::fromStdString(product.name())
                                         + " | " + QString::fromStdString(categoryToString(product.category()))
                                         + " | " + QString::number(product.price()) + " KRW"
                                         + " | Stock " + QString::number(product.stock()));
        item->setData(Qt::UserRole, product.id());
        productList->addItem(item);
    }
}
