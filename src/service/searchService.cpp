#include "searchService.h"
#include "productService.h"


Products SearchService::allProducts(int pageIndex) {
    if (productService == nullptr || pageIndex < 0) {return {};}
    if (currentProducts.empty() || currentSearchType != SearchType::All) {
        currentProducts.clear();
        currentProducts = productService->getAll();
        currentSearchType = SearchType::All;
    }
    return filterIndex(pageIndex);
}


Products SearchService::getCategoryProducts(Category category, int pageIndex) {
    if (productService == nullptr || pageIndex < 0) {return {};}
    if (currentProducts.empty() || currentSearchType != SearchType::Category) {
        currentProducts.clear();
        currentProducts = productService->getByCategory(category);
        currentCategory = category;
        currentSearchType = SearchType::Category;
    }
    return filterIndex(pageIndex);
}


Products SearchService::searchProducts(const string& keyword, int pageIndex) {
    if (productService == nullptr || pageIndex < 0 || currentProducts.empty()) {return {};}
    return filterIndex(pageIndex);
}

Products SearchService::getProducts(SearchType type, optional<string> keyword, optional<Category> category, int pageIndex) {
    if (productService == nullptr || pageIndex < 0) {return {};}
    switch (type) {
        case SearchType::All:
            return allProducts(pageIndex);
        case SearchType::Category:
            if (!category.has_value()) {return {};}
            return getCategoryProducts(category.value(), pageIndex);
        default:
            return {};
     }
}


Products SearchService::filterIndex(int pageIndex, Products products) const {
    Products pool;
    if (products.empty()) {
        pool = currentProducts;
    } else {
        pool = products;
    }
    if (pool.empty() || pageIndex < 0) {return {};}
    const int begin = pageIndex * ItemsPerPage;
    const int end = begin + ItemsPerPage < static_cast<int>(pool.size())
            ? begin + ItemsPerPage
            : static_cast<int>(pool.size());
    return {pool.begin() + begin, pool.begin() + end};
}