#include "productGridPage.h"
#include "ElaDef.h"
#include "ElaIconButton.h"
#include "ElaLineEdit.h"
#include "loginPage.h"

#include <ElaFlowLayout.h>
#include <ElaPopularCard.h>
#include <ElaText.h>
#include <QVBoxLayout>
#include <qboxlayout.h>
#include <qdebug.h>

void ProductGridPage::initPage() {
    setWindowTitle("Products");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);
    initLayout();
}

void ProductGridPage::initLayout() {
    auto* titleText = new ElaText("Products", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Browse sportwear inventory.", this);
    descText->setTextPixelSize(16);

    auto* titleLayout = new QVBoxLayout();
    titleLayout->setContentsMargins(20, 10, 20, 10);
    titleLayout->addWidget(titleText);
    titleLayout->addWidget(descText);

    productLayout = new ElaFlowLayout(0, 10, 10);
    productLayout->setContentsMargins(0, 0, 0, 0);
    productLayout->setIsAnimation(true);

    auto* leftEndArrow = new ElaIconButton(ElaIconType::AnglesLeft);
    leftEndArrow->setFixedWidth(40);
    auto* leftArrow = new ElaIconButton(ElaIconType::AngleLeft);
    leftArrow->setFixedWidth(40);
    pageIndex = new ElaText("1");
    pageIndex->setFixedWidth(30);
    pageIndex->setFixedHeight(30);
    pageIndex->setAlignment(Qt::AlignCenter);
    pageIndex->setTextPixelSize(12);
    auto* pageIndexInput = new ElaLineEdit();
    pageIndexInput->setFixedWidth(50);
    pageIndexInput->setFixedHeight(30);
    auto* rightArrow = new ElaIconButton(ElaIconType::AngleRight);
    rightArrow->setFixedWidth(40);
    auto* rightEndArrow = new ElaIconButton(ElaIconType::AnglesRight);
    rightEndArrow->setFixedWidth(40);

    auto* indexLayout = new QHBoxLayout();
    indexLayout->addWidget(pageIndex);
    indexLayout->addSpacing(20);
    indexLayout->addWidget(pageIndexInput);

    auto* pageIndexLayout = new QHBoxLayout();
    pageIndexLayout->addStretch();
    pageIndexLayout->addWidget(leftEndArrow);
    pageIndexLayout->addWidget(leftArrow);
    pageIndexLayout->addSpacing(20);
    pageIndexLayout->addLayout(indexLayout);
    pageIndexLayout->addSpacing(20);
    pageIndexLayout->addWidget(rightArrow);
    pageIndexLayout->addWidget(rightEndArrow);
    pageIndexLayout->addStretch();
    

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Products");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->addLayout(titleLayout);
    centerLayout->addSpacing(12);
    centerLayout->addLayout(productLayout);
    centerLayout->addStretch();
    centerLayout->addLayout(pageIndexLayout);

    addCentralWidget(centralWidget, true, false, 0);
}

void ProductGridPage::setProducts(std::vector<Product> products) {
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

void ProductGridPage::addProductCard(const Product& product) {
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