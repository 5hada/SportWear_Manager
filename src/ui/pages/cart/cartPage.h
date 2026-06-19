#pragma once

#include "ElaScrollPage.h"

#include "app/eventHandler.h"

class ElaIconButton;
class ElaTableView;
class ElaText;
class QStandardItemModel;

class CartPage: public ElaScrollPage {
    Q_OBJECT

    ElaTableView* cartTable{nullptr};
    QStandardItemModel* model{nullptr};
    ElaText* pageText{nullptr};
    ElaIconButton* previousButton{nullptr};
    ElaIconButton* nextButton{nullptr};
    ElaText* totalCountText{nullptr};
    ElaText* totalPriceText{nullptr};

    void clearRow(int row);
    void setPageInfo(int currentPage, int maxPage);

public:
    explicit CartPage(QWidget* parent = nullptr);

    void refreshContent(const CartPageContent& content);

Q_SIGNALS:
    void pageMoveRequested(int delta);
    void orderRequested();

    void cartRequest(CartAction action, int productId = -1, int count = 0, std::optional<bool> isSelected = std::nullopt);
};
