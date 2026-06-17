#pragma once

#include "ElaScrollPage.h"

class ElaTableView;
class ElaText;
class QStandardItemModel;

class CartPage: public ElaScrollPage {
    QStandardItemModel* model{nullptr};
    ElaTableView* cartTable{nullptr};
    ElaText* totalCountText{nullptr};
    ElaText* totalPriceText{nullptr};

public:
    explicit CartPage(QWidget* parent = nullptr);
};
