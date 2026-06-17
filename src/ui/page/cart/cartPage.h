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

public:
    explicit CartPage(QWidget* parent = nullptr);

    void setCart(const Cart& cart);

Q_SIGNALS:
    void orderRequested();
};
