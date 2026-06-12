#pragma once

#include <ElaScrollPage.h>

#include "model/product/product.h"

class ElaText;

class ProductDetailPage : public ElaScrollPage{
    Q_OBJECT

    Product product;
    ElaText* nameText{nullptr};
    ElaText* priceText{nullptr};
    ElaText* stockText{nullptr};
    ElaText* detailText{nullptr};

    void refresh();

public:
    explicit ProductDetailPage(QWidget* parent = nullptr);
    ~ProductDetailPage() override;

    void setProduct(const Product& product);

Q_SIGNALS:
    void addCartRequested(int productId);
    void addWishRequested(int productId);
};
