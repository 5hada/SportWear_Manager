#include "productGridPage.h"
#include "ElaDef.h"
#include "ElaIconButton.h"
#include "ElaLineEdit.h"

#include <ElaFlowLayout.h>
#include <ElaText.h>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QString>
#include <QVBoxLayout>
#include <qboxlayout.h>
#include <qdebug.h>

ProductGridPage::ProductGridPage(QWidget* parent): ElaScrollPage(parent) {
    initPage();
    initLayout();
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

    initIndexNavigation();
    
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

    connect(searchEdit, &ElaLineEdit::textChanged, this, [this]() {
        currentPage = 0;
        rebuildProducts();
    });
}

void ProductGridPage::initIndexNavigation() {
    auto* leftEndArrow = new ElaIconButton(ElaIconType::AnglesLeft);
    leftEndArrow->setFixedWidth(40);
    auto* leftArrow = new ElaIconButton(ElaIconType::AngleLeft);
    leftArrow->setFixedWidth(40);
    pageIndex = new ElaText("1");
    pageIndex->setFixedWidth(70);
    pageIndex->setFixedHeight(30);
    pageIndex->setAlignment(Qt::AlignCenter);
    pageIndex->setTextPixelSize(12);
    pageIndexInput = new ElaLineEdit();
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

    indexNavigation = new QHBoxLayout();
    indexNavigation->addStretch();
    indexNavigation->addWidget(leftEndArrow);
    indexNavigation->addWidget(leftArrow);
    indexNavigation->addSpacing(20);
    indexNavigation->addLayout(indexLayout);
    indexNavigation->addSpacing(20);
    indexNavigation->addWidget(rightArrow);
    indexNavigation->addWidget(rightEndArrow);
    indexNavigation->addStretch();

    connect(leftEndArrow, &ElaIconButton::clicked, this, [this]() {
        setCurrentPage(0);
    });
    connect(leftArrow, &ElaIconButton::clicked, this, [this]() {
        setCurrentPage(currentPage - 1);
    });
    connect(rightArrow, &ElaIconButton::clicked, this, [this]() {
        setCurrentPage(currentPage + 1);
    });
    connect(rightEndArrow, &ElaIconButton::clicked, this, [this]() {
        setCurrentPage(pageCount(filteredProducts().size()) - 1);
    });
    connect(pageIndexInput, &ElaLineEdit::textChanged, this, [this](const QString& text) {
        bool ok = false;
        const int page = text.toInt(&ok);
        if (ok) {
            setCurrentPage(page - 1);
        }
    });
}

void ProductGridPage::setProducts(std::vector<Product> products) {
    this->products = std::move(products);
    currentPage = 0;
    rebuildProducts();
}

void ProductGridPage::rebuildProducts() {
    while (auto* item = productLayout->takeAt(0)) {
        if (auto* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    const auto filtered = filteredProducts();
    const int totalPages = pageCount(filtered.size());
    if (currentPage >= totalPages) {
        currentPage = totalPages - 1;
    }
    if (currentPage < 0) {
        currentPage = 0;
    }

    const int begin = currentPage * PageSize;
    const int end = begin + PageSize < static_cast<int>(filtered.size())
        ? begin + PageSize
        : static_cast<int>(filtered.size());

    for (int index = begin; index < end; ++index) {
        addProductCard(filtered[index]);
    }
    updatePageControls(totalPages);
}

bool ProductGridPage::matchesSearch(const Product& product) const {
    if (searchEdit == nullptr || searchEdit->text().trimmed().isEmpty()) {
        return true;
    }

    const auto query = searchEdit->text().trimmed();
    return QString::fromStdString(product.getName()).contains(query, Qt::CaseInsensitive)
        || QString::fromStdString(product.getDetail()).contains(query, Qt::CaseInsensitive)
        || QString::fromStdString(categoryToString(product.getCategory())).contains(query, Qt::CaseInsensitive);
}

Products ProductGridPage::filteredProducts() const {
    Products filtered;
    for (const auto& product : products) {
        if (matchesSearch(product)) {
            filtered.emplace_back(product);
        }
    }
    return filtered;
}

int ProductGridPage::pageCount(int itemCount) const {
    if (itemCount <= 0) {
        return 1;
    }
    return (itemCount + PageSize - 1) / PageSize;
}

void ProductGridPage::setCurrentPage(int page) {
    const int totalPages = pageCount(filteredProducts().size());
    if (page < 0) {
        page = 0;
    }
    if (page >= totalPages) {
        page = totalPages - 1;
    }
    if (currentPage == page) {
        updatePageControls(totalPages);
        return;
    }
    currentPage = page;
    rebuildProducts();
}

void ProductGridPage::updatePageControls(int totalPages) {
    pageIndex->setText(QString("%1 / %2").arg(currentPage + 1).arg(totalPages));
    const QString currentPageText = QString::number(currentPage + 1);
    if (pageIndexInput->text() != currentPageText) {
        pageIndexInput->setText(currentPageText);
    }
}

void ProductGridPage::addProductCard(const Product& product) {
    auto* productCard = new QPushButton(this);
    productCard->setCursor(Qt::PointingHandCursor);
    productCard->setFixedWidth(320);
    productCard->setMinimumHeight(132);
    productCard->setFlat(true);
    productCard->setStyleSheet(
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

    auto* imageLabel = new QLabel(productCard);
    imageLabel->setFixedSize(72, 72);
    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(QPixmap(":/Resource/Image/Cirno.jpg"));

    auto* nameText = new ElaText(product.getName().empty()
        ? "Sample Product"
        : QString::fromStdString(product.getName()), productCard);
    nameText->setTextPixelSize(18);
    nameText->setWordWrap(true);

    auto* categoryText = new ElaText(QString::fromStdString(categoryToString(product.getCategory())), productCard);
    categoryText->setTextPixelSize(13);

    auto* priceText = new ElaText(QString("Price %1").arg(product.getPrice()), productCard);
    priceText->setTextPixelSize(14);

    auto* stockText = new ElaText(QString("Stock %1").arg(product.getStock()), productCard);
    stockText->setTextPixelSize(14);

    auto* detailText = new ElaText(product.getDetail().empty()
        ? "No detail."
        : QString::fromStdString(product.getDetail()), productCard);
    detailText->setTextPixelSize(12);
    detailText->setWordWrap(true);

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

    auto* cardLayout = new QHBoxLayout(productCard);
    cardLayout->setContentsMargins(14, 12, 14, 12);
    cardLayout->setSpacing(12);
    cardLayout->addWidget(imageLabel);
    cardLayout->addLayout(textLayout);

    connect(productCard, &QPushButton::clicked, this, [this, product]() {
        Q_EMIT productSelected(product);
    });
    productLayout->addWidget(productCard);
}
