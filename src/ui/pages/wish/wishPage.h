#pragma once

#include <ElaScrollPage.h>

#include "model/ui/wishPageContent.h"

#include <vector>

class ElaTableView;
class ElaText;
class ElaIconButton;
class ElaPushButton;
class QStandardItemModel;
class QWidget;

class WishPage: public ElaScrollPage {
    Q_OBJECT

    struct RowWidgets {
        QWidget* actions{nullptr};
        ElaPushButton* cartButton{nullptr};
        ElaPushButton* removeButton{nullptr};
        int productId{-1};
    };

    ElaTableView* wishTable{nullptr};
    QStandardItemModel* model{nullptr};
    ElaText* pageText{nullptr};
    ElaIconButton* previousButton{nullptr};
    ElaIconButton* nextButton{nullptr};
    std::vector<RowWidgets> rows;

    void clearRow(int row);
    void setPageInfo(int currentPage, int maxPage);

public:
    explicit WishPage(QWidget* parent = nullptr);

    void refreshContent(const WishPageContent& content);

Q_SIGNALS:
    void pageMoveRequested(int delta);
    void cartRequested(int productId);
    void removeRequested(int productId);
};
