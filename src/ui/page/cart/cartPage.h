#pragma once

#include "ElaScrollPage.h"
#include "model/product/cart.h"

#include "model/actions.h"

class ElaTableView;
class ElaText;
class QStandardItemModel;

class CartPage: public ElaScrollPage {
    Q_OBJECT

    QStandardItemModel* model{nullptr};
    ElaTableView* cartTable{nullptr};
    ElaText* totalCountText{nullptr};
    ElaText* totalPriceText{nullptr};

    int selectedProductId() const;
    bool selectedProductIsSelected() const;

public:
    explicit CartPage(QWidget* parent = nullptr);

    void setCart(const Cart& cart);

Q_SIGNALS:
    void orderRequested();

    void cartRequest(CartAction action, int productId = -1, int count = 0, std::optional<bool> isSelected = std::nullopt);
};
