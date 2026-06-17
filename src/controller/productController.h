#include "model/product/product.h"


class ProductController {


public:
    ProductController();

    Products getAll();
    Products getCategory();
    Products getWishAll();
    Product getProduct(int productId);

    bool setWish(int productId);
};