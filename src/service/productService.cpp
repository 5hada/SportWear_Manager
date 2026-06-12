#include "productService.h"

ProductService::ProductService(ProductRepository *products) : products_(products) {}

std::vector<Product> ProductService::listProducts() const {
    if (products_ == nullptr) {
        return {};
    }
    return products_->findAll();
}

std::optional<Product> ProductService::getProduct(int id) const {
    if (products_ == nullptr) {
        return std::nullopt;
    }
    return products_->findById(id);
}

void ProductService::saveProduct(const Product &product) {
    if (products_ != nullptr) {
        products_->save(product);
    }
}
