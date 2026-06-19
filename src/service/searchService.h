
#include "model/product/product.h"
#include <optional>

using std::optional;

class ProductService;

class SearchService {
    ProductService* productService{nullptr};

    Products currentProducts;
    int currentMaxIndex{-1};
    Category currentSearchType{Category::Unknown};

    static constexpr int ItemsPerPage = 50;
public:
    SearchService() {}

    void setProductService(ProductService* productService) {this->productService = productService;}

    Products allProducts(int pageIndex);
    Products getCategoryProducts(Category category, int pageIndex);

    Products filterIndex(int pageIndex, Products products = {}) const;
    Products filterKeyword(const string& keyword, int pageIndex);

    int getMaxPageIndex(const string& keyword, Category category = Category::Unknown) const;
    Products getProducts(const string& keyword, int pageIndex, Category category = Category::Unknown);

    Products searchProducts(const string& keyword, int pageIndex);
};