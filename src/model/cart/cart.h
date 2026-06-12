#include "cartItem.h"
#include <vector>

class Cart {
    std::vector<CartItem> items_;

public:
    const std::vector<CartItem> &items() const;

    void addItem(const Product &product, int quantity);
    bool removeItem(int productId);
    void clear();
    int totalPrice() const;
};
