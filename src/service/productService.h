#include "database/repository/productRepository.h"

#include <optional>
#include <vector>

class ProductService {
    ProductRepository *products = nullptr;
public:
    ProductService(ProductRepository *products);

    std::vector<Product> listProducts() const;
    std::optional<Product> getProduct(int id) const;
    void saveProduct(const Product &product);
};
