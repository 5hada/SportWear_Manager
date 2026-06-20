#include "productCard.h"

#include <QLabel>
#include <ElaText.h>
#include <QFontMetrics>
#include <QPixmap>
#include <QVBoxLayout>


namespace {
QString productImagePath(const std::string& category) {
    if (category == "Top") {
        return ":/images/product_top.png";
    }
    if (category == "Bottom") {
        return ":/images/product_bottom.png";
    }
    if (category == "Shoes") {
        return ":/images/product_shoes.png";
    }
    if (category == "Accessory") {
        return ":/images/product_accessory.png";
    }
    return ":/images/product_unknown.png";
}

void setElidedText(ElaText* label, const QString& text, int width) {
    if (label == nullptr) {
        return;
    }
    label->setToolTip(text);
    label->setText(label->fontMetrics().elidedText(text, Qt::ElideRight, width));
}
}

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
    productImage->setPixmap(QPixmap(":/images/product_unknown.png"));

    nameText = new ElaText("Product Name", this);
    nameText->setTextPixelSize(18);
    nameText->setWordWrap(false);

    categoryText = new ElaText("Category", this);
    categoryText->setTextPixelSize(13);

    priceText = new ElaText("Price", this);
    priceText->setTextPixelSize(14);

    stockText = new ElaText("Stock", this);
    stockText->setTextPixelSize(14);

    detailText = new ElaText("Product Detail", this);
    detailText->setWordWrap(false);
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

void ProductCard::setContent(const ProductCardContent& content) {
    productId = content.id;
    productImage->setPixmap(QPixmap(productImagePath(content.category)));
    constexpr int textWidth = 190;
    constexpr int metaWidth = 86;
    setElidedText(nameText, QString::fromStdString(content.name), textWidth);
    setElidedText(categoryText, QString::fromStdString(content.category), textWidth);
    setElidedText(priceText, QString("Price %1").arg(content.price), metaWidth);
    setElidedText(stockText, QString("Stock %1").arg(content.stock), metaWidth);
    setElidedText(detailText, QString::fromStdString(content.detail.empty()
        ? "No detail."
        : content.detail), textWidth);
}
