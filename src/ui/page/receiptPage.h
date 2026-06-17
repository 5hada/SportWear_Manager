#pragma once

#include <ElaScrollPage.h>
#include <vector>

#include "model/product/receipt.h"

class ElaFlowLayout;

class ReceiptPage: public ElaScrollPage {
    Q_OBJECT

public:
    explicit ReceiptPage(QWidget* parent = nullptr);
    ~ReceiptPage() override;

    void setReceipts(std::vector<Receipt> receipts);

private:
    void rebuildReceipts();
    void addReceiptCard(const Receipt& receipt);

    std::vector<Receipt> receipts;
    ElaFlowLayout* receiptLayout{nullptr};
};
