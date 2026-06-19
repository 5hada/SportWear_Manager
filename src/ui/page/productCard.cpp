#include "productCard.h"

#include <QLabel>
#include <ElaText.h>
#include <QVBoxLayout>



ProductCard::ProductCard(QWidget* parent): ElaPushButton(parent) {
    setCursor(Qt::PointingHandCursor);
    setFixedWidth(320);
    setMinimumHeight(132);
    setFlat(true);
    setStyleSheet(
        "QPushButton {"
        "  text-align: left;"
        "  border: 1px solid rgba(120, 120, 120, 80);"
        "  border-radius: 6px;"
        "  background: rgba(255, 255, 255, 18);"
        "}"
        "QPushButton:hover {"
        "  border-color: rgba(80, 140, 220, 180);"
        "  background: rgba(80, 140, 220, 24);"
        "}"
    );

    productImage = new QLabel(this);
    productImage->setFixedSize(72, 72);
    productImage->setScaledContents(true);
    productImage->setPixmap(QPixmap(":/Resource/Image/Cirno.jpg"));

    nameText = new ElaText("Product Name", this);
    nameText->setTextPixelSize(18);
    nameText->setWordWrap(true);

    categoryText = new ElaText("Category", this);
    categoryText->setTextPixelSize(13);

    priceText = new ElaText("Price", this);
    priceText->setTextPixelSize(14);

    stockText = new ElaText("Stock", this);
    stockText->setTextPixelSize(14);

    detailText = new ElaText("Product Detail", this);
    detailText->setWordWrap(true);
    detailText->setTextPixelSize(12);

    auto* metaLayout = new QHBoxLayout();
    metaLayout->setContentsMargins(0, 0, 0, 0);
    metaLayout->addWidget(priceText);
    metaLayout->addSpacing(12);
    metaLayout->addWidget(stockText);
    metaLayout->addStretch();

    auto* textLayout = new QVBoxLayout();
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(8);
    textLayout->addWidget(nameText);
    textLayout->addWidget(categoryText);
    textLayout->addLayout(metaLayout);
    textLayout->addWidget(detailText);
    textLayout->addStretch();

    auto* cardLayout = new QHBoxLayout(this);
    cardLayout->setContentsMargins(14, 12, 14, 12);
    cardLayout->setSpacing(12);
    cardLayout->addWidget(productImage);
    cardLayout->addLayout(textLayout);

    connect(this, &QPushButton::clicked, this, [this]() {
        emit selected(productId);
    });

    hide();
}

void ProductCard::setProduct(const Product& product) {
    productId = product.getId();
    nameText->setText(QString::fromStdString(product.getName()));
    categoryText->setText(QString::fromStdString(categoryToString(product.getCategory())));
    priceText->setText(QString("Price %1").arg(product.getPrice()));
    stockText->setText(QString("Stock %1").arg(product.getStock()));
    detailText->setText(QString::fromStdString(product.getDetail().empty()
        ? "No detail."
        : product.getDetail()));
}