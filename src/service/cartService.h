
#include "model/product/cart.h"
#include "model/product/cartAction.h"
#include <optional>

class CartRepository;
class ProductRepository;
class CartService {
    CartRepository* cartRepo = nullptr;
    ProductRepository* productRepo = nullptr;

    bool checkReposExist() const;
    bool checkProductExist(int productId) const;

    bool add(int userId, int productId, int count, std::optional<bool> isSelected);
    bool sub(int userId, int productId, int count, std::optional<bool> isSelected);
    bool set(int userId, int productId, int count, std::optional<bool> isSelected);
    bool toggle(int userId, int productId, std::optional<bool> isSelected);
    bool del(int userId, int productId);
    bool clear(int userId);
public:
    CartService(
        CartRepository* cartRepo,
        ProductRepository* productRepo
    ): cartRepo(cartRepo), productRepo(productRepo){}

    void setCartRepo(CartRepository* cartRepo) {this->cartRepo = cartRepo;}
    void setProductRepo(ProductRepository* productRepo) {this->productRepo = productRepo;}

    Cart getCart(int userId) const;

    bool handleCart(
        CartAction action,
        int userId,
        int productId = 0,
        int count = 0,
        std::optional<bool> isSelected = std::nullopt);
};
