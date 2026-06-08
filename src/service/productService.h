#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H

#include "database/repository/productRepository.h"

#include <optional>
#include <vector>

class ProductService {
public:
    explicit ProductService(ProductRepository *products);

    std::vector<Product> listProducts() const;
    std::optional<Product> getProduct(int id) const;
    void saveProduct(const Product &product);

private:
    ProductRepository *products_ = nullptr;
};

#endif // PRODUCTSERVICE_H
