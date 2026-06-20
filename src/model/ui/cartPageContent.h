#pragma once

#include "model/product/cart.h"
#include "model/ui/pageNavigationContent.h"

#include <string>
#include <vector>

struct CartPageContent : PageNavigationContent {
    Cart cart;
    std::vector<std::string> productNames;
    std::vector<int> itemTotals;
    int totalCount{0};
    int totalPrice{0};
};
