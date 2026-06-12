#include "productRepository.h"
#include <algorithm>

ProductRepository::ProductRepository() {
    save(Product(1, "Training T-Shirt", Category::Top, 29000, 30));
    save(Product(2, "Running Pants", Category::Bottom, 49000, 20));
    save(Product(3, "Court Shoes", Category::Shoes, 89000, 12));
    save(Product(4, "Gym Bag", Category::Accessory, 39000, 18));
}

const std::vector<Product> &ProductRepository::findAll() const {
    return products_;
}

std::optional<Product> ProductRepository::findById(int id) const {
    for (const auto &product : products_) {
        if (product.id() == id) {
            return product;
        }
    }
    return std::nullopt;
}

void ProductRepository::save(const Product &product) {
    for (auto &stored : products_) {
        if (stored.id() == product.id()) {
            stored = product;
            return;
        }
    }
    products_.push_back(product);
}

bool ProductRepository::remove(int id) {
    const auto originalSize = products_.size();
    products_.erase(std::remove_if(products_.begin(), products_.end(), [id](const Product &product) {
                        return product.id() == id;
                    }),
                    products_.end());
    return products_.size() != originalSize;
}
