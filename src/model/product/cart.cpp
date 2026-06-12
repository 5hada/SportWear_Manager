#include "cart.h"
#include <algorithm>

const std::vector<Item> &Cart::getItems() const {
    return items;
}

void Cart::addItem(int productId, int count) {
    addItem(productId, count, 0);
}

void Cart::addItem(int productId, int count, int price) {
    for (auto &item : items) {
        if (item.id == productId) {
            item.count += count;
            item.price = price;
            return;
        }
    }
    items.emplace_back(productId, count, price);
}

bool Cart::subItem(int productId, int count) {
    for (auto &item : items) {
        if (item.id == productId) {
            if (item.count > count){
                item.count-= count;
                return true;
            }
            else if (item.count == count){
                removeItem(productId);
                return true;
            }
            return false;
        }
    }
    return false;
}

bool Cart::removeItem(int productId) {
    const auto originalSize = items.size();
    items.erase(std::remove_if(items.begin(), items.end(), [productId](const Item &item) {
                     return item.id == productId;
                 }),
                 items.end());
    return items.size() != originalSize;
}

void Cart::clear() {
    items.clear();
}

int Cart::getTotalPrice() const {
    int total = 0;
    for (const auto &item : items) {
        total += (item.price*item.count);
    }
    return total;
}
