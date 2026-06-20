#pragma once

#include <ElaPushButton.h>

#include "model/ui/productPageContent.h"

class QLabel;
class ElaText;

class ProductCard: public ElaPushButton {
    Q_OBJECT

    QLabel* productImage{nullptr};
    ElaText* nameText{nullptr};
    ElaText* categoryText{nullptr};
    ElaText* priceText{nullptr};
    ElaText* stockText{nullptr};
    ElaText* detailText{nullptr};
    int productId = -1;

public:
    explicit ProductCard(QWidget* parent = nullptr);

    void setContent(const ProductCardContent& content);
    
Q_SIGNALS:
    void selected(int productId);
};
