#pragma once

#include "ElaScrollPage.h"

#include "model/actions.h"
#include "model/ui/cartPageContent.h"

#include <vector>

class ElaCheckBox;
class ElaIconButton;
class ElaPushButton;
class ElaSpinBox;
class ElaTableView;
class ElaText;
class QStandardItemModel;
class QWidget;

class CartPage: public ElaScrollPage {
    Q_OBJECT

    struct RowWidgets {
        QWidget* selectedCell{nullptr};
        ElaCheckBox* selectedCheck{nullptr};
        QWidget* quantityCell{nullptr};
        ElaSpinBox* quantitySpin{nullptr};
        QWidget* actions{nullptr};
        ElaPushButton* decreaseButton{nullptr};
        ElaPushButton* increaseButton{nullptr};
        ElaPushButton* removeButton{nullptr};
        int productId{-1};
    };

    ElaTableView* cartTable{nullptr};
    QStandardItemModel* model{nullptr};
    ElaText* pageText{nullptr};
    ElaIconButton* previousButton{nullptr};
    ElaIconButton* nextButton{nullptr};
    ElaText* totalCountText{nullptr};
    ElaText* totalPriceText{nullptr};
    std::vector<RowWidgets> rows;

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
