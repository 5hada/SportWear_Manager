#pragma once

#include <ElaScrollPage.h>

#include "model/product/product.h"

class ElaTableView;
class QStandardItemModel;

class WishPage: public ElaScrollPage {
    Q_OBJECT
\
    ElaTableView* wishTable{nullptr};
    QStandardItemModel* model{nullptr};
    Products wishs;

    void rebuildRows();
public:
    explicit WishPage(QWidget* parent = nullptr);

    void setWishs(Products wishs) {this->wishs = std::move(wishs);}
};
