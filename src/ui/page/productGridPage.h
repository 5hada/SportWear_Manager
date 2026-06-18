#pragma once

#include <ElaScrollPage.h>

#include "model/product/product.h"

class ElaFlowLayout;
class ElaLineEdit;
class ElaText;
class QHBoxLayout;

class ProductGridPage: public ElaScrollPage {
    Q_OBJECT

    Products products;
    ElaFlowLayout* productLayout{nullptr};
    QHBoxLayout* indexNavigation;
    ElaText* pageIndex;
    ElaLineEdit* pageIndexInput{nullptr};
    ElaLineEdit* searchEdit{nullptr};
    int currentPage{0};
    static constexpr int PageSize = 12;

    void initPage();
    void initLayout();
    void initIndexNavigation();
    void initConnect();
    void initCard();

    void addProductCard(const Product& product);
    void rebuildProducts();
    bool matchesSearch(const Product& product) const;
    Products filteredProducts() const;
    int pageCount(int itemCount) const;
    void setCurrentPage(int page);
    void updatePageControls(int totalPages);
    void detailRequest(int productId);
public:
    explicit ProductGridPage(QWidget* parent = nullptr);

    void setProducts(Products products);

Q_SIGNALS:
    void productSelected(const Product& product);
};
