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
    ElaLineEdit* searchEdit{nullptr};

    void initPage();
    void initLayout();
    void initIndexNavigation();
    void initConnect();
    void initCard();

    void addProductCard(const Product& product);
    void rebuildProducts();
    bool matchesSearch(const Product& product) const;
    void detailRequest(int productId);
public:
    explicit ProductGridPage(QWidget* parent = nullptr);

    void setProducts(Products products);

Q_SIGNALS:
    void productSelected(const Product& product);
};
