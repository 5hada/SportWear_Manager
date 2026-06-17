#pragma once

#include <ElaScrollPage.h>
#include <vector>

#include "model/product/product.h"

class ElaFlowLayout;

class ProductGridPage : public ElaScrollPage {
    Q_OBJECT

    std::vector<Product> products;
    ElaFlowLayout* productLayout{nullptr};
    ElaText* pageIndex;

    void initPage();
    void initLayout();
    void initConnect();
    void initCard();

    void addProductCard(const Product& product);
    void rebuildProducts();
    void detailRequest(int productId);
public:
    explicit ProductGridPage(QWidget* parent): ElaScrollPage(parent) {initPage();}
    ~ProductGridPage() override = default;

    void setProducts(std::vector<Product> products);

Q_SIGNALS:
    void productSelected(const Product& product);
};
