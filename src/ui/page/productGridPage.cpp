#include "productGridPage.h"
#include "indexNavigation.h"
#include "productCard.h"

#include "ElaLineEdit.h"
#include <ElaFlowLayout.h>
#include <ElaText.h>
#include <QLabel>
#include <ElaPushButton.h>
#include <QPixmap>
#include <QString>
#include <QVBoxLayout>
#include <qboxlayout.h>
#include <qdebug.h>

ProductGridPage::ProductGridPage(int ItemsPerPage, QWidget* parent): ElaScrollPage(parent) {
    ProductGridPage::ItemsPerPage = ItemsPerPage;
    initPage();
    initLayout();
    initConnect();
}

void ProductGridPage::initPage() {
    setWindowTitle("Products");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);
}

void ProductGridPage::initLayout() {
    auto* titleText = new ElaText("Products", this);
    titleText->setTextPixelSize(35);

    auto* descText = new ElaText("Browse sportwear inventory.", this);
    descText->setTextPixelSize(16);

    searchEdit = new ElaLineEdit(this);
    searchEdit->setPlaceholderText("Search products");
    searchEdit->setFixedHeight(36);

    auto* titleLayout = new QVBoxLayout();
    titleLayout->setContentsMargins(20, 10, 20, 10);
    titleLayout->addWidget(titleText);
    titleLayout->addWidget(descText);
    titleLayout->addSpacing(12);
    titleLayout->addWidget(searchEdit);

    productLayout = new ElaFlowLayout(0, 10, 10);
    productLayout->setContentsMargins(0, 0, 0, 0);
    productLayout->setIsAnimation(true);

    for (int i = 0; i < ItemsPerPage; ++i) {
        auto* productCard = new ProductCard(this);
        productCards.push_back(productCard);
        productLayout->addWidget(productCard);
    }

    indexNavigation = new IndexNavigation(this);
    
    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Products");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->addLayout(titleLayout);
    centerLayout->addSpacing(12);
    centerLayout->addLayout(productLayout);
    centerLayout->addStretch();
    centerLayout->addLayout(indexNavigation);

    addCentralWidget(centralWidget, true, false, 0);
}

void ProductGridPage::initConnect() {
    connect(searchEdit, &ElaLineEdit::returnPressed, this, [this]() {
        emit searchRequested(searchEdit->text().toStdString());
    });

    connect(indexNavigation, &IndexNavigation::indexChanged, this, [this](int newIndex) {
        emit pageIndexChanged(newIndex);
    });

    for (auto* productCard : productCards) {
        connect(productCard, &ProductCard::selected, this, [this](int productId) {
            emit productSelected(productId);
        });
    }
}

void ProductGridPage::setContents(std::tuple<const Products&, int, int> contents) {
    const auto& [products, pageIndex, maxPageIndex] = contents;
    indexNavigation->setIndex(maxPageIndex, pageIndex);
    setProductCards(products);
}

void ProductGridPage::setProductCards(const Products& products) {
    int count = static_cast<int>(products.size());
    if (count > ItemsPerPage) {count = ItemsPerPage;}
    for (int i = 0; i < count; ++i) {
        productCards[i]->show();
        productCards[i]->setProduct(products[i]);
    }
    if (count < ItemsPerPage) {
        for (int i = count; i < ItemsPerPage; ++i) {
            productCards[i]->hide();
        }
    }
}