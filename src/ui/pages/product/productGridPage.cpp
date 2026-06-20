#include "productGridPage.h"
#include "ui/components/indexNavigation.h"
#include "ui/components/productCard.h"

#include "ElaLineEdit.h"
#include <ElaComboBox.h>
#include <ElaFlowLayout.h>
#include <ElaText.h>
#include <QLabel>
#include <ElaPushButton.h>
#include <QPixmap>
#include <QSignalBlocker>
#include <QString>
#include <QVBoxLayout>
#include <qboxlayout.h>
#include <qdebug.h>

ProductGridPage::ProductGridPage(int itemsPerPage, QWidget* parent): ElaScrollPage(parent) {
    this->itemsPerPage = itemsPerPage;
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

    addButton = new ElaPushButton("Add", this);
    addButton->setFixedSize(90, 34);
    addButton->hide();

    auto* titleRow = new QHBoxLayout();
    titleRow->setContentsMargins(0, 0, 0, 0);
    titleRow->addWidget(titleText);
    titleRow->addStretch();
    titleRow->addWidget(addButton);

    auto* descText = new ElaText("Browse sportwear inventory.", this);
    descText->setTextPixelSize(16);

    searchEdit = new ElaLineEdit(this);
    searchEdit->setPlaceholderText("Search products");
    searchEdit->setFixedHeight(36);

    categoryCombo = new ElaComboBox(this);
    categoryCombo->setFixedSize(180, 36);
    categoryCombo->addItem("All", QVariant::fromValue(static_cast<int>(Category::Unknown)));
    for (auto category: Categories) {
        if (category == Category::Unknown) {
            continue;
        }
        categoryCombo->addItem(
            QString::fromStdString(categoryToString(category)),
            QVariant::fromValue(static_cast<int>(category))
        );
    }

    auto* searchLayout = new QHBoxLayout();
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(10);
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(categoryCombo);

    auto* titleLayout = new QVBoxLayout();
    titleLayout->setContentsMargins(20, 10, 20, 10);
    titleLayout->addLayout(titleRow);
    titleLayout->addWidget(descText);
    titleLayout->addSpacing(12);
    titleLayout->addLayout(searchLayout);

    productLayout = new ElaFlowLayout(0, 10, 10);
    productLayout->setContentsMargins(0, 0, 0, 0);
    productLayout->setIsAnimation(true);

    for (int i = 0; i < itemsPerPage; ++i) {
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
    connect(addButton, &ElaPushButton::clicked, this, &ProductGridPage::addRequested);

    connect(categoryCombo, QOverload<int>::of(&ElaComboBox::currentIndexChanged), this,
            [this](int index) {
                const auto category = static_cast<Category>(categoryCombo->itemData(index).toInt());
                emit categoryChanged(category);
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

void ProductGridPage::setContents(const ProductGridPageContent& content) {
    indexNavigation->setIndex(content.maxPage, content.currentPage);
    setProductCards(content.products);
}

void ProductGridPage::setCategory(Category category) {
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

void ProductGridPage::setAdminMode(bool isAdmin) {
    if (addButton != nullptr) {
        addButton->setVisible(isAdmin);
    }
}

void ProductGridPage::setProductCards(const Products& products) {
    int count = static_cast<int>(products.size());
    const int cardCount = static_cast<int>(productCards.size());
    if (count > cardCount) {count = cardCount;}
    for (int i = 0; i < count; ++i) {
        productCards[i]->show();
        productCards[i]->setProduct(products[i]);
    }
    for (int i = count; i < cardCount; ++i) {
        productCards[i]->hide();
    }
}
