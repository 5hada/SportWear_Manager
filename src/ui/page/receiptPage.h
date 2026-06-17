#pragma once

#include <ElaScrollPage.h>

#include "model/product/receipt.h"

class ElaFlowLayout;

class ReceiptPage: public ElaScrollPage {
    Q_OBJECT

    Receipts receipts;
    ElaFlowLayout* receiptLayout{nullptr};

    void rebuildReceipts();
    void addReceiptCard(const Receipt& receipt);
public:
    explicit ReceiptPage(QWidget* parent = nullptr);

    void setReceipts(Receipts receipts);
};
