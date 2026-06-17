#include "cart.h"
// #include <algorithm>


void Cart::addItem(int productId, int count) {
    items.emplace_back(productId, count);
}

void Cart::addItem(CartItem item) {
    items.emplace_back(item);
}

// bool Cart::subItem(int productId, int count) {
//     for (auto &item : items) {
//         if (item.id == productId) {
//             if (item.count > count){
//                 item.count-= count;
//                 return true;
//             }
//             else if (item.count == count){
//                 removeItem(productId);
//                 return true;
//             }
//             return false;
//         }
//     }
//     return false;
// }

// bool Cart::removeItem(int productId) {
//     const auto originalSize = items.size();
//     items.erase(std::remove_if(items.begin(), items.end(), [productId](const Item &item) {
//                      return item.id == productId;
//                  }),
//                  items.end());
//     return items.size() != originalSize;
// }

// void Cart::clear() {
//     items.clear();
// }

int Cart::getTotalPrice() const {
    int total = 0;
    for (const auto &item : items) {
        total += (item.price*item.count);
    }
    return total;
}


int Cart::getTotalCount() const {
    return items.size();
}
