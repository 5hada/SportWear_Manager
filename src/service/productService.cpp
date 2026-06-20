#include "productService.h"

using std::nullopt;

Products ProductService::getAll() const {
    if (!isRepoValid()) {
        return {};
    }
    return productRepo->findAll();
}

Products ProductService::getByCategory(Category category) const {
    Products products;
    for (const auto& product : getAll()) {
        if (category == Category::Unknown || product.getCategory() == category) {
            products.emplace_back(product);
        }
    }
    return products;
}

Product ProductService::getById(int id) const {
   if (getOptById(id) != nullopt){
     return getOptById(id).value();
   }
   return Product();
}

bool ProductService::add(const Product& product) {
    if (!isRepoValid()) {return false;}
    if (product.getPrice() < 0 || product.getStock() < 0 || product.getName().empty()) {return false;}
    if (product.getId() <= 0 || getOptById(product.getId()) == nullopt){
        return productRepo->insert(product);
    }
    return false;
}

bool ProductService::update(const Product& product) {
    if (!isRepoValid() || !isExist(product.getId())) {return false;}
    if (product.getPrice() < 0 || product.getStock() < 0 || product.getName().empty()) {return false;}
    return productRepo->update(product);
}

bool ProductService::decreaseStock(int productId, int count) {
    if (count <= 0 || !isExist(productId)) {return false;}
    Product product(getById(productId));
    if (!product.decreaseStock(count)) {return false;}
    return productRepo->update(product);
}

bool ProductService::increaseStock(int productId, int count) {
    if (count <= 0 || !isExist(productId)) {return false;}
    Product product(getById(productId));
    product.increaseStock(count);
    return productRepo->update(product);
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


bool ProductService::isExist(const Product& product) {
    return !(getOptById(product.getId()) == nullopt);
}

bool ProductService::isExist(int id) {
    return getOptById(id) != nullopt;
}

bool ProductService::isRepoValid() const{
    return (productRepo != nullptr);
}



optional<Product> ProductService::getOptById(int id) const {
    if (!isRepoValid()) {
        return nullopt;
    }
    return productRepo->findById(id);
}
