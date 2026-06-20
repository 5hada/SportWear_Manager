#include "model/product/product.h"

class WishRepository;
class ProductRepository;

class WishService {
    WishRepository* wishRepo{nullptr};
    ProductRepository* productRepo{nullptr};
    
    bool isRepoValid();
public:
    WishService(WishRepository* wishRepo, ProductRepository* productRepo):
        wishRepo(wishRepo), productRepo(productRepo){}

    Products getWishs(int userId);

    bool add(int userId, int productId);
    bool remove(int userId, int productId);
};
