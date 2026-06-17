
#include "model/product/cart.h"

#include "model/product/cartAction.h"
class CartController {


public:
    CartController();

    Cart getCart();
    bool handleCart(CartAction action, int productId, int count);
};