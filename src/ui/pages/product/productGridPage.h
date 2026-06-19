#pragma once

#include <ElaScrollPage.h>
#include <tuple>

#include "model/product/category.h"
#include "model/product/product.h"

class ElaFlowLayout;
class ElaLineEdit;
class ElaPushButton;
class ElaComboBox;
class ProductCard;
class IndexNavigation;

class ProductGridPage: public ElaScrollPage {
    Q_OBJECT

    ElaFlowLayout* productLayout{nullptr};
    ElaLineEdit* searchEdit{nullptr};
    ElaComboBox* categoryCombo{nullptr};
    ElaPushButton* addButton{nullptr};
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
    void setCategory(Category category);
    void setAdminMode(bool isAdmin);

Q_SIGNALS:
    void searchRequested(const string& keyword);
    void categoryChanged(Category category);
    void pageIndexChanged(int newIndex);
    void addRequested();
    void productSelected(int productId);
};
