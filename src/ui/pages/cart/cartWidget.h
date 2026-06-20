#pragma once


#include <ElaWidgetTools/ElaDockWidget.h>
#include "model/ui/cartWidgetContent.h"

class ElaTableView;
class QStandardItemModel;

class CartWidget: public ElaDockWidget {
    Q_OBJECT

    QStandardItemModel* model{nullptr};
    ElaTableView* cartList{nullptr};
    
public:
    explicit CartWidget(QWidget* parent = nullptr);

    void setContent(const CartWidgetContent& content);
};
