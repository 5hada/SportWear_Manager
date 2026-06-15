#include "productDetailPage.h"

#include <ElaPushButton.h>
#include <ElaText.h>
#include <QHBoxLayout>
#include <QVBoxLayout>

ProductDetailPage::ProductDetailPage(QWidget* parent)
    : ElaScrollPage(parent),
      product(ProductItem{24, 59000}, "Running Jacket", Category::Unknown)
{
    setWindowTitle("Product Detail");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Product Detail", this);
    titleText->setTextPixelSize(35);

    nameText = new ElaText(this);
    nameText->setTextPixelSize(24);

    priceText = new ElaText(this);
    priceText->setTextPixelSize(18);

    stockText = new ElaText(this);
    stockText->setTextPixelSize(18);

    detailText = new ElaText(this);
    detailText->setTextPixelSize(15);

    auto* addCartButton = new ElaPushButton("Add to Cart", this);
    auto* wishButton = new ElaPushButton("Add Wish", this);

    connect(addCartButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT addCartRequested(product.getId());
    });
    connect(wishButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT addWishRequested(product.getId());
    });

    auto* actionLayout = new QHBoxLayout();
    actionLayout->setSpacing(10);
    actionLayout->addWidget(addCartButton);
    actionLayout->addWidget(wishButton);
    actionLayout->addStretch();

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Product Detail");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(14);
    centerLayout->addWidget(titleText);
    centerLayout->addSpacing(12);
    centerLayout->addWidget(nameText);
    centerLayout->addWidget(priceText);
    centerLayout->addWidget(stockText);
    centerLayout->addWidget(detailText);
    centerLayout->addSpacing(12);
    centerLayout->addLayout(actionLayout);
    centerLayout->addStretch();

    refresh();
    addCentralWidget(centralWidget, true, false, 0);
}

ProductDetailPage::~ProductDetailPage() = default;

void ProductDetailPage::setProduct(const Product& product)
{
    this->product = product;
    refresh();
}

void ProductDetailPage::refresh()
{
    nameText->setText(product.getName().empty() ? "Running Jacket" : QString::fromStdString(product.getName()));
    priceText->setText(QString("Price: %1").arg(product.getPrice()));
    stockText->setText(QString("Stock: %1").arg(product.getStock()));
    detailText->setText(product.getDetail().empty()
                            ? "No detail."
                            : QString::fromStdString(product.getDetail()));
}
