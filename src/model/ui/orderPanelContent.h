#pragma once

#include "model/product/order.h"

struct OrderPanelContent {
    Order order;
    int totalPrice{0};
    int availablePoints{0};
    int maxUsablePoint{0};
    int payment{0};
};
