#pragma once

#include <ElaScrollPage.h>
#include <QString>

#include "model/product/receipt.h"

class ElaTableView;
class QStandardItemModel;

class ReceiptPage: public ElaScrollPage {
    Q_OBJECT

    Receipts receipts;
    ElaTableView* receiptTable{nullptr};
    QStandardItemModel* model{nullptr};

    void rebuildReceipts();
    int selectedReceiptId() const;
    static QString itemSummary(const Receipt& receipt);
public:
    explicit ReceiptPage(QWidget* parent = nullptr);

    void setReceipts(Receipts receipts);

Q_SIGNALS:
    void refundRequested(int receiptId);
};
