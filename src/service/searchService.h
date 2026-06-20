#include "model/product/category.h"
#include "model/product/product.h"

#include <optional>

using std::optional;
using std::nullopt;

enum class SearchMode {
    All,
    Keyword
};

class ProductService;

class SearchService {
    ProductService* productService{nullptr};

    SearchMode currentMode = SearchMode::All;

    Products productsPool;
    Products filteredProducts;

    int currentIndex = -1;
    int currentMaxIndex = -1;

    Product currentProduct;

    static constexpr int ItemsPerPage = 50;

    void setSearchMode(SearchMode mode) {currentMode = mode;}
    SearchMode getSearchMode() const {return currentMode;}

    bool matchesSearch(const Product& product);
public:
    SearchService() {}

    void setProductService(ProductService* productService) {this->productService = productService;}


    bool setMaxIndex();
    int getMaxIndex() const;

    bool setCurrentIndex(int newIndex);
    int getCurrentIndex() const;

    bool setProductsPool(optional<Category> category = nullopt);
    bool searchProducts(const string& keyword);
    Products getProducts();

    
    bool setCurrentProduct(int productId);
    Product getCurrentProduct() const;
};