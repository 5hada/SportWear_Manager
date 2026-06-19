#pragma once

#include <ElaScrollPage.h>
#include <tuple>

#include "model/product/product.h"

class ElaFlowLayout;
class ElaLineEdit;
class ProductCard;
class IndexNavigation;

class ProductGridPage: public ElaScrollPage {
    Q_OBJECT

    ElaFlowLayout* productLayout{nullptr};
    ElaLineEdit* searchEdit{nullptr};
    IndexNavigation* indexNavigation{nullptr};
    std::vector<ProductCard*> productCards;

    void initPage();
    void initLayout();
    void initConnect();

    void setProductCards(const Products& products);

    int itemsPerPage;
public:
    ProductGridPage(int ItemsPerPage, QWidget* parent = nullptr);

    void setContents(std::tuple<Products, int, int>);

Q_SIGNALS:
    void searchRequested(const string& keyword);
    void pageIndexChanged(int newIndex);
    void productSelected(int productId);
};
