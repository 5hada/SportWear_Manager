#pragma once

#include <ElaScrollPage.h>

#include "model/product/product.h"

class ElaText;

class ProductDetailPage : public ElaScrollPage {
    Q_OBJECT

    Product product;
    ElaText* nameText{nullptr};
    ElaText* priceText{nullptr};
    ElaText* stockText{nullptr};
    ElaText* detailText{nullptr};
    int selectedCount;

    void initPage();
    void refresh();

public:
    explicit ProductDetailPage(QWidget* parent): ElaScrollPage(parent) {initPage();}
    ~ProductDetailPage() override = default;

    void setProduct(const Product& product);

Q_SIGNALS:
    void backRequested();
    void orderRequest(int productId, int count = 1);
    void cartRequest(int productId, int count = 1);
    void wishRequest(int productId);
};
