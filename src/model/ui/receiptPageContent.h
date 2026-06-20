#pragma once

#include "model/product/receipt.h"
#include "model/ui/pageNavigationContent.h"

#include <string>
#include <vector>

struct ReceiptPageContent : PageNavigationContent {
    Receipts receipts;
    std::vector<std::string> itemSummaries;
    std::vector<bool> refundable;
};
