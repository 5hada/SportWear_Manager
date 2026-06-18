#pragma once

#include <ElaScrollPage.h>

#include "model/product/product.h"

class ElaTableView;
class QStandardItemModel;

class WishPage: public ElaScrollPage {
    Q_OBJECT

    ElaTableView* wishTable{nullptr};
    QStandardItemModel* model{nullptr};
    Products wishs;

    void rebuildRows();
    int selectedProductId() const;
public:
    explicit WishPage(QWidget* parent = nullptr);

    void setWishs(Products wishs);

Q_SIGNALS:
    void productSelected(int productId);
    void removeRequested(int productId);
};
