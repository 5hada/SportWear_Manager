#pragma once

#include "database/databaseManager.h"
#include "database/repository/cartRepository.h"
#include "database/repository/orderRepository.h"
#include "database/repository/productRepository.h"
#include "database/repository/receiptRepository.h"
#include "database/repository/reviewRepository.h"
#include "database/repository/userRepository.h"
#include "database/repository/wishRepository.h"

#include <string>

class RepositoryProvider {
public:
    DataBaseManager database;

    CartRepository cart;
    OrderRepository order;
    ProductRepository product;
    ReceiptRepository receipt;
    ReviewRepository review;
    UserRepository user;
    WishRepository wish;

    explicit RepositoryProvider(
        const std::string& databasePath = "sportwear.db",
        const std::string& schemaPath = "schema.sql")
        : user(&database),
          order(&database),
          product(&database),
          cart(&database),
          receipt(&database),
          review(&database),
          wish(&database)
    {
        databaseReady = database.initialize(databasePath, schemaPath);
        seedProducts();
    }

    bool isDatabaseReady() const { return databaseReady; }

private:
    void seedProducts()
    {
        if (!databaseReady || !product.findAll().empty()) {
            return;
        }

        Product shirt(Item{1, 30, 29000}, "Training T-Shirt", Category::Top);
        shirt.setDetail("Breathable short-sleeve training top.");
        product.save(shirt);

        Product pants(Item{2, 20, 49000}, "Running Pants", Category::Bottom);
        pants.setDetail("Lightweight pants for daily running.");
        product.save(pants);

        Product shoes(Item{3, 12, 89000}, "Court Shoes", Category::Shoes);
        shoes.setDetail("Stable court shoes for indoor sports.");
        product.save(shoes);

        Product bag(Item{4, 18, 39000}, "Gym Bag", Category::Accessory);
        bag.setDetail("Compact bag with separated shoe storage.");
        product.save(bag);
    }

    bool databaseReady = false;
};
