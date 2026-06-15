
#include "model/product/cart.h"
#include "model/product/cartAction.h"

class CartRepository;
class ProductRepository;
class CartService {
    CartRepository* cartRepo = nullptr;
    ProductRepository* productRepo = nullptr;

    bool checkReposExist() const;
    bool checkProductExist(int productId) const;

    bool add(int userId, int productId, int count);
    bool sub(int userId, int productId, int count);
    bool set(int userId, int productId, int count);
    bool del(int userId, int productId);
    bool clear(int userId);
public:
    explicit CartService(
        CartRepository* cartRepo,
        ProductRepository* productRepo
    ): cartRepo(cartRepo), productRepo(productRepo){}

    Cart getCart(int userId) const;

    bool handleCart(CartAction action, int userId, int productId=0, int count=0);
};
