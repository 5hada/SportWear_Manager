#pragma once

#include "ElaDialog.h"
#include "model/product/order.h"

class QStandardItemModel;
class ElaTableView;
class ElaText;
class ElaSpinBox;

class OrderPanel: public ElaDialog {
    Q_OBJECT

    QStandardItemModel* model{nullptr};
    ElaTableView* orderTable{nullptr};
    ElaText* totalText{nullptr};
    ElaText* pointText{nullptr};
    ElaText* paidText{nullptr};
    ElaSpinBox* pointSpin{nullptr};

public:
    explicit OrderPanel(QWidget* parent = nullptr);

    void setOrder(Order order, int totalPrice, int availablePoints, int maxUsablePoint, int payment);
    void setPayment(int payment);

Q_SIGNALS:
    void pointChanged(int usedPoint);
    void confirmRequested(int usedPoint);
    void cancelRequested();
};
