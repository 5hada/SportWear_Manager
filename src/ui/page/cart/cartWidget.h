#pragma once

#include "cartList.h"

#include <ElaWidgetTools/ElaDockWidget.h>
#include "model/product/cart.h"

class QStandardItemModel;

class CartWidget : public ElaDockWidget
{
    Q_OBJECT

public:
    explicit CartWidget(QWidget* parent = nullptr);
    ~CartWidget() override;

    void setCart(const Cart& cart);

private:
    CartList* cartList{nullptr};
    QStandardItemModel* model{nullptr};
};
