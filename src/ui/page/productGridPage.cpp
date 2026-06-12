#include "productGridPage.h"

#include <ElaFlowLayout.h>
#include <ElaPopularCard.h>
#include <ElaText.h>
#include <QVBoxLayout>

ProductGridPage::ProductGridPage(QWidget* parent)
    : ElaScrollPage(parent)
{
    setWindowTitle("Products");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* titleText = new ElaText("Products", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Browse sportwear inventory.", this);
    descText->setTextPixelSize(16);

    productLayout = new ElaFlowLayout(0, 10, 10);
    productLayout->setContentsMargins(0, 0, 0, 0);
    productLayout->setIsAnimation(true);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Products");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(12);
    centerLayout->addLayout(productLayout);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);

}

ProductGridPage::~ProductGridPage() = default;

void ProductGridPage::setProducts(std::vector<Product> products)
{
    this->products = std::move(products);
    rebuildProducts();
}

void ProductGridPage::rebuildProducts()
{
    while (auto* item = productLayout->takeAt(0)) {
        if (auto* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    for (const auto& product : products) {
        addProductCard(product);
    }
}

void ProductGridPage::addProductCard(const Product& product)
{
    auto* productCard = new ElaPopularCard(this);
    productCard->setCardPixmap(QPixmap(":/Resource/Image/Cirno.jpg"));
    productCard->setTitle(product.getName().empty() ? "Sample Product" : QString::fromStdString(product.getName()));
    productCard->setSubTitle(QString("Price %1 / Stock %2").arg(product.getPrice()).arg(product.getStock()));
    productCard->setInteractiveTips("Detail");
    productCard->setDetailedText(product.getDetail().empty()
                                     ? "No detail."
                                     : QString::fromStdString(product.getDetail()));
    connect(productCard, &ElaPopularCard::popularCardClicked, this, [this, product]() {
        Q_EMIT productSelected(product);
    });
    connect(productCard, &ElaPopularCard::popularCardButtonClicked, this, [this, product]() {
        Q_EMIT productSelected(product);
    });
    productLayout->addWidget(productCard);
}
