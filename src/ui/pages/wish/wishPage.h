#pragma once

#include <ElaScrollPage.h>

#include "app/eventHandler.h"

class ElaTableView;
class ElaText;
class ElaIconButton;
class QStandardItemModel;

class WishPage: public ElaScrollPage {
    Q_OBJECT

    ElaTableView* wishTable{nullptr};
    QStandardItemModel* model{nullptr};
    ElaText* pageText{nullptr};
    ElaIconButton* previousButton{nullptr};
    ElaIconButton* nextButton{nullptr};

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
