#pragma once

#include <ElaScrollPage.h>

#include "app/eventHandler.h"

class ElaIconButton;
class ElaTableView;
class ElaText;
class QStandardItemModel;

class ReceiptPage: public ElaScrollPage {
    Q_OBJECT

    ElaTableView* receiptTable{nullptr};
    QStandardItemModel* model{nullptr};
    ElaText* pageText{nullptr};
    ElaIconButton* previousButton{nullptr};
    ElaIconButton* nextButton{nullptr};

    void clearRow(int row);
    void setPageInfo(int currentPage, int maxPage);
public:
    explicit ReceiptPage(QWidget* parent = nullptr);

    void refreshContent(const ReceiptPageContent& content);

Q_SIGNALS:
    void pageMoveRequested(int delta);
    void refundRequested(int receiptId);
};
