#include "productService.h"
#include <optional>


std::vector<Product> ProductService::getAll() const {
    if (!isRepoValid()) {
        return {};
    }
    return productRepo->findAll();
}

std::optional<Product> ProductService::getOptById(int id) const {
    if (!isRepoValid()) {
        return std::nullopt;
    }
    return productRepo->findById(id);
}

Product ProductService::getById(int id) const {
   if (getOptById(id) != std::nullopt){
     return getOptById(id).value();
   }
   return Product();
}

bool ProductService::add(const Product& product) {
    if (getOptById(product.getId()) == std::nullopt){
        return productRepo->insert(product);
    }
    return false;
}

bool ProductService::setPrice(int productId, int price) {
    if (isExist(productId)) {
        Product product(getById(productId));
        product.setPrice(price);
        return productRepo->update(product);
    }
    return false;
}

bool ProductService::setStock(int productId, int stock) {
    if (isExist(productId)) {
        Product product(getById(productId));
        product.setStock(stock);
        return productRepo->update(product);
    }
    return false;
}


bool ProductService::isRepoValid() const{
    return (productRepo != nullptr);
}

bool ProductService::isExist(const Product& product) {
    return !(getOptById(product.getId()) == std::nullopt);
}

bool ProductService::isExist(int id) {
    return getOptById(id) != std::nullopt;
}
