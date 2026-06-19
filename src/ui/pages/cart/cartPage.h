#pragma once

#include "ElaScrollPage.h"

#include "model/product/cart.h"
#include "model/actions.h"

class ElaTableView;
class ElaText;
class QStandardItemModel;

class CartPage: public ElaScrollPage {
    Q_OBJECT

    Cart currentCart;
    QStandardItemModel* model{nullptr};
    ElaTableView* cartTable{nullptr};
    ElaText* totalCountText{nullptr};
    ElaText* totalPriceText{nullptr};

    int findRow(int productId) const;
    CartItem* findItem(int productId);
    void appendItemRow(const CartItem& item);
    void updateItemRow(int row, const CartItem& item);
    void removeProductRow(int productId);
    void removeProductRowLater(int productId);
    void resizeTableColumns();
    void refreshSummary();

public:
    explicit CartPage(QWidget* parent = nullptr);

    void setCart(const Cart& cart);
    void syncCart(const Cart& cart);
    void restoreProductRow(int productId);

Q_SIGNALS:
    void orderRequested();

    void cartRequest(CartAction action, int productId = -1, int count = 0, std::optional<bool> isSelected = std::nullopt);
};
