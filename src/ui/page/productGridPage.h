#pragma once

#include <ElaScrollPage.h>
#include <vector>

#include "model/product/product.h"

class ElaFlowLayout;

class ProductGridPage : public ElaScrollPage{
    Q_OBJECT

public:
    explicit ProductGridPage(QWidget* parent = nullptr);
    ~ProductGridPage() override;

    void setProducts(std::vector<Product> products);

Q_SIGNALS:
    void productSelected(const Product& product);

private:
    void rebuildProducts();
    void addProductCard(const Product& product);

    std::vector<Product> products;
    ElaFlowLayout* productLayout{nullptr};
};
