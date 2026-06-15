#include "database/repository/productRepository.h"

#include <optional>
#include <vector>

class ProductService {
    ProductRepository *productRepo = nullptr;

    bool isRepoValid() const;
    bool isExist(const Product& product);
    bool isExist(int id);
public:
    ProductService(ProductRepository *productRepo): productRepo(productRepo) {}

    std::vector<Product> getAll() const;
    // std::vector<Product> getByCategory() const;
    std::optional<Product> getOptById(int id) const;
    Product getById(int id) const;

    bool add(const Product &product);
    bool setStock(int productId, int stock);
    bool setPrice(int productId, int price);
};
