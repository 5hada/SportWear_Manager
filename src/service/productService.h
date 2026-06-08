#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H

#include "database/repository/productRepository.h"

class ProductService {
public:
    explicit ProductService(ProductRepository *products) : products_(products) {}

    std::vector<Product> listProducts() const
    {
        if (products_ == nullptr) {
            return {};
        }
        return products_->findAll();
    }

    std::optional<Product> getProduct(int id) const
    {
        if (products_ == nullptr) {
            return std::nullopt;
        }
        return products_->findById(id);
    }

    void saveProduct(const Product &product)
    {
        if (products_ != nullptr) {
            products_->save(product);
        }
    }

private:
    ProductRepository *products_ = nullptr;
};

#endif // PRODUCTSERVICE_H
