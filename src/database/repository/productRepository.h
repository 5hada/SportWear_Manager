#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H

#include "model/product/product.h"

#include <optional>
#include <vector>

class ProductRepository {
public:
    ProductRepository();

    const std::vector<Product> &findAll() const;
    std::optional<Product> findById(int id) const;
    void save(const Product &product);
    bool remove(int id);

private:
    std::vector<Product> products_;
};

#endif // PRODUCTREPOSITORY_H
