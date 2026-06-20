#pragma once

#include <ElaScrollPage.h>

#include "model/ui/receiptPageContent.h"

#include <vector>

class ElaIconButton;
class ElaPushButton;
class ElaTableView;
class ElaText;
class QStandardItemModel;
class QWidget;

class ReceiptPage: public ElaScrollPage {
    Q_OBJECT

    struct RowWidgets {
        QWidget* refundCell{nullptr};
        ElaPushButton* refundButton{nullptr};
        int receiptId{-1};
    };

    ElaTableView* receiptTable{nullptr};
    QStandardItemModel* model{nullptr};
    ElaText* pageText{nullptr};
    ElaIconButton* previousButton{nullptr};
    ElaIconButton* nextButton{nullptr};
    std::vector<RowWidgets> rows;

    void clearRow(int row);
    void setPageInfo(int currentPage, int maxPage);
public:
    explicit ReceiptPage(QWidget* parent = nullptr);

    void refreshContent(const ReceiptPageContent& content);

Q_SIGNALS:
    void pageMoveRequested(int delta);
    void refundRequested(int receiptId);
};
