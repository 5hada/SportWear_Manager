#include "searchService.h"
#include "productService.h"
#include <sstream>


bool SearchService::setMaxIndex() {
    int size = (currentMode == SearchMode::Keyword) ? filteredProducts.size() : productsPool.size();
    if (size < 0) {return false;}
    if (size < ItemsPerPage) {
        currentMaxIndex = 0;
    }
    else {
        currentMaxIndex = size / ItemsPerPage;
    }
    return true;
}
int SearchService::getMaxIndex() const {return currentMaxIndex;}


bool SearchService::setCurrentIndex(int newIndex) {
    if (newIndex < 0 || newIndex > currentMaxIndex) {return false;}
    currentIndex = newIndex;
    return true;
}
int SearchService::getCurrentIndex() const {return currentIndex;}



bool SearchService::setProductsPool(optional<Category> category) {
    if (productService == nullptr) {return false;}
    setSearchMode(SearchMode::All);
    productsPool.clear();
    if (category == nullopt) {
        productsPool = productService->getAll();
        return true;
    }
    else {
        productsPool = productService->getByCategory(category.value());
        return true;
    }
}

bool SearchService::searchProducts(const string& keyword) {
    if (productService == nullptr) {return false;}
    setSearchMode(SearchMode::Keyword);
    filteredProducts.clear();
    std::vector<std::string> keywords;
    std::stringstream ss(keyword);
    std::string word;
    while (ss >> word) {
        keywords.push_back(word);
    }

    for (const auto& product : productsPool) {
        bool matched = true;
        for (const auto& word : keywords) {
            if (product.getName().find(word) == std::string::npos) {
                matched = false;
                break;
            }
        }
        if (matched) {
            filteredProducts.push_back(product);
        }
    }
    return true;
}



Products SearchService::getProducts() {
    Products& pool = (currentMode == SearchMode::Keyword) ? filteredProducts : productsPool;
    int begin = currentIndex*ItemsPerPage;
    int end = (currentIndex == currentMaxIndex) ?
        pool.size() : begin + ItemsPerPage;
    return {pool.begin() + begin, pool.end() + end};
}







bool SearchService::setCurrentProduct(int productId) {
    currentProduct = productService->getById(productId);
    if (currentProduct.getId() != productId) {return false;}
    return true;
};

Product SearchService::getCurrentProduct() const {
    return currentProduct;
}