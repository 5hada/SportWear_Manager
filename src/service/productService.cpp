#include "productService.h"

ProductService::ProductService(ProductRepository *products) : products(products) {}

std::vector<Product> ProductService::listProducts() const {
    if (products == nullptr) {
        return {};
    }
    return products->findAll();
}

std::optional<Product> ProductService::getProduct(int id) const {
    if (products == nullptr) {
        return std::nullopt;
    }
    return products->findById(id);
}

void ProductService::saveProduct(const Product &product) {
    if (products != nullptr) {
        products->insert(product);
    }
}
