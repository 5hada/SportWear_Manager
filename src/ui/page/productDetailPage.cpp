#include "productDetailPage.h"
#include "ElaDef.h"
#include "ElaIconButton.h"

#include <ElaPushButton.h>
#include <ElaText.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qboxlayout.h>


void ProductDetailPage::initPage() {
    setWindowTitle("Product Detail");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Product Detail");
    titleText->setTextPixelSize(35);

    nameText = new ElaText();
    nameText->setTextPixelSize(24);

    priceText = new ElaText();
    priceText->setTextPixelSize(18);

    stockText = new ElaText();
    stockText->setTextPixelSize(18);

    detailText = new ElaText();
    detailText->setTextPixelSize(15);
    detailText->setWordWrap(true);

    auto* textLayout = new QVBoxLayout();
    textLayout->setSpacing(14);
    textLayout->addWidget(titleText);
    textLayout->addSpacing(12);
    textLayout->addWidget(nameText);
    textLayout->addWidget(priceText);
    textLayout->addWidget(stockText);
    textLayout->addWidget(detailText);

    auto* addCartButton = new ElaIconButton(ElaIconType::Heart);
    auto* wishButton = new ElaPushButton("Add Wish");
    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    buttonLayout->addWidget(wishButton);
    buttonLayout->addWidget(addCartButton);

    auto* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(30, 20, 30, 20);
    mainLayout->addLayout(textLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(addCartButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT cartRequest(product.getId());
    });
    connect(wishButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT wishRequest(product.getId());
    });
    refresh();
}

void ProductDetailPage::setProduct(const Product& product) {
    this->product = product;
    refresh();
}

void ProductDetailPage::refresh() {
    nameText->setText(product.getName().empty() ?
        "Unknown" : QString::fromStdString(product.getName()));
    priceText->setText(QString("Price: %1").arg(product.getPrice()));
    stockText->setText(QString("Stock: %1").arg(product.getStock()));
    detailText->setText(product.getDetail().empty() ?
        "No detail." : QString::fromStdString(product.getDetail()));
}
