#pragma once

#include "ElaDialog.h"
#include "model/product/order.h"

class QStandardItemModel;
class ElaTableView;
class ElaText;

class OrderPanel: public ElaDialog {
    Q_OBJECT

    QStandardItemModel* model{nullptr};
    ElaTableView* orderTable{nullptr};
    ElaText* totalText{nullptr};
    ElaText* pointText{nullptr};
    ElaText* paidText{nullptr};

public:
    explicit OrderPanel(QWidget* parent = nullptr);

    void setOrder(Order order);

Q_SIGNALS:
    void confirmRequested(long long usedPoint);
    void cancelRequested();
};
