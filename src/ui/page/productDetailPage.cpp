#include "productDetailPage.h"
#include "ElaDef.h"
#include "ElaIconButton.h"

#include <ElaPushButton.h>
#include <ElaText.h>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qboxlayout.h>


void ProductDetailPage::initPage() {
    setWindowTitle("Product Detail");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* backButton = new ElaIconButton(ElaIconType::AngleLeft, this);
    backButton->setFixedSize(40, 40);

    auto* titleText = new ElaText("Product Detail", this);
    titleText->setTextPixelSize(35);

    auto* titleRow = new QHBoxLayout();
    titleRow->setSpacing(12);
    titleRow->addWidget(backButton);
    titleRow->addWidget(titleText);
    titleRow->addStretch();

    nameText = new ElaText(this);
    nameText->setTextPixelSize(24);

    priceText = new ElaText(this);
    priceText->setTextPixelSize(18);

    stockText = new ElaText(this);
    stockText->setTextPixelSize(18);

    detailText = new ElaText(this);
    detailText->setTextPixelSize(15);
    detailText->setWordWrap(true);

    auto* textLayout = new QVBoxLayout();
    textLayout->setSpacing(14);
    textLayout->addLayout(titleRow);
    textLayout->addSpacing(12);
    textLayout->addWidget(nameText);
    textLayout->addWidget(priceText);
    textLayout->addWidget(stockText);
    textLayout->addWidget(detailText);

    auto* addCartButton = new ElaIconButton(ElaIconType::CartShopping, this);
    auto* wishButton = new ElaPushButton("Add Wish", this);
    auto* buyButton = new ElaPushButton("Buy Now", this);
    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    buttonLayout->addWidget(wishButton);
    buttonLayout->addWidget(addCartButton);
    buttonLayout->addWidget(buyButton);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Product Detail");

    auto* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(30, 20, 30, 20);
    mainLayout->addLayout(textLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);

    connect(backButton, &ElaIconButton::clicked, this, &ProductDetailPage::backRequest);
    connect(addCartButton, &ElaIconButton::clicked, this, [this]() {
        Q_EMIT cartRequest(product.getId());
    });
    connect(wishButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT wishRequest(product.getId());
    });
    connect(buyButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT orderRequest(product.getId(), 1);
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
