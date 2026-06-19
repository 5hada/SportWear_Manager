#pragma once

#include <ElaScrollPage.h>
#include <QString>
#include <string>
#include <vector>

#include "model/product/receipt.h"

class ElaTableView;
class QStandardItemModel;

class ReceiptPage: public ElaScrollPage {
    Q_OBJECT

    Receipts receipts;
    std::vector<std::string> itemSummaries;
    ElaTableView* receiptTable{nullptr};
    QStandardItemModel* model{nullptr};

    void rebuildReceipts();
    int selectedReceiptId() const;
public:
    explicit ReceiptPage(QWidget* parent = nullptr);

    void setReceipts(Receipts receipts, std::vector<std::string> itemSummaries);

Q_SIGNALS:
    void refundRequested(int receiptId);
};
