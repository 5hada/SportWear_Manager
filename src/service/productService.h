#include "database/repository/productRepository.h"

class ProductService {
    ProductRepository *productRepo = nullptr;

    bool isRepoValid() const;
    std::optional<Product> getOptById(int id) const;
public:
    ProductService(ProductRepository *productRepo): productRepo(productRepo) {}

    Products getAll() const;
    // std::vector<Product> getByCategory() const;
    Product getById(int id) const;

    bool isExist(const Product& product);
    bool isExist(int id);

    bool add(const Product &product);
    bool setStock(int productId, int stock);
    bool setPrice(int productId, long long price);
};
