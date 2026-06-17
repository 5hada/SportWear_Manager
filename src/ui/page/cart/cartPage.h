#pragma once

#include "ElaScrollPage.h"
#include "model/product/cart.h"

class ElaTableView;
class ElaText;
class QStandardItemModel;

class CartPage: public ElaScrollPage {
    Q_OBJECT

    QStandardItemModel* model{nullptr};
    ElaTableView* cartTable{nullptr};
    ElaText* totalCountText{nullptr};
    ElaText* totalPriceText{nullptr};

    int selectedProductId() const;
    bool selectedProductIsSelected() const;

public:
    explicit CartPage(QWidget* parent = nullptr);

    void setCart(const Cart& cart);

Q_SIGNALS:
    void increaseRequested(int productId);
    void decreaseRequested(int productId);
    void toggleSelectedRequested(int productId, bool isSelected);
    void removeRequested(int productId);
    void clearRequested();
    void orderRequested();
};
