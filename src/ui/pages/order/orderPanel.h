#pragma once

#include "ElaDialog.h"
#include "model/ui/orderPanelContent.h"

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

    void setContent(const OrderPanelContent& content);
    void setPayment(int payment);

Q_SIGNALS:
    void pointChanged(int usedPoint);
    void confirmRequested(int usedPoint);
    void cancelRequested();
};
