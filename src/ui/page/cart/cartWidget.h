#pragma once


#include <ElaWidgetTools/ElaDockWidget.h>
#include "model/product/cart.h"

class ElaTableView;
class QStandardItemModel;

class CartWidget : public ElaDockWidget
{
    Q_OBJECT

public:
    explicit CartWidget(QWidget* parent = nullptr);
    ~CartWidget() override;

    void setCart(const Cart& cart);

private:
    ElaTableView* cartList{nullptr};
    QStandardItemModel* model{nullptr};
};
