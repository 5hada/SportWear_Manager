#pragma once


#include <ElaWidgetTools/ElaDockWidget.h>
#include "model/product/cart.h"

class ElaTableView;
class QStandardItemModel;

class CartWidget: public ElaDockWidget {
    Q_OBJECT

    QStandardItemModel* model{nullptr};
    ElaTableView* cartList{nullptr};
    
public:
    explicit CartWidget(QWidget* parent = nullptr);

    void setCart(const Cart& cart);
};
