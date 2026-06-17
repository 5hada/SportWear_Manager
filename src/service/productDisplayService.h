
#include "model/product/product.h"

class ProductService;

class ProductDisplayService {
    ProductService* productService{nullptr};

    Products products;

    static constexpr int ItemsPerPage = 50;
public:
    ProductDisplayService(ProductService* productService): productService(productService) {}

    Products getProducts(int pageIndex);
    Products getCategoryProducts(int pageIndex, Category category);
};