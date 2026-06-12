#include "model/product/product.h"
#include <optional>
#include <vector>

class ProductRepository {
    std::vector<Product> products_;

public:
    ProductRepository();

    const std::vector<Product> &findAll() const;
    std::optional<Product> findById(int id) const;
    void save(const Product &product);
    bool remove(int id);
};
