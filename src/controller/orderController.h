
#include "model/product/receipt.h"

class OrderController {


public:
    OrderController();

    Receipts getReceipts();
    bool refund(int receiptId);
};