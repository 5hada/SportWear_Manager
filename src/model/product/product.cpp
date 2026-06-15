#include "product.h"



bool Product::hasStock(int count) const {
    return count > 0 && item.count >= count;
}

bool Product::decreaseStock(int count) {
bool Product::decreaseStock(int count) {
    if (!hasStock(count)) {
        return false;
    }
    item.count -= count;
    return true;
}

void Product::increaseStock(int count) {
    item.count += count;
}
