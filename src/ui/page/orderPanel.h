
#pragma once

#include "ElaScrollPage.h"

class ElaTableView;
class QStandardItemModel;
class ElaText;

class OrderPanel: public ElaScrollPage {
    QStandardItemModel* model{nullptr};
    ElaTableView* orderTable{nullptr};
    ElaText* totalText{nullptr};
    ElaText* pointText{nullptr};
    ElaText* paidText{nullptr};

public:
    explicit OrderPanel(QWidget* parent = nullptr);
};
