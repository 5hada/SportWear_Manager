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
    bool databaseReady = false;


    void seedProducts();

    static std::string resolveSchemaPath(const std::string& schemaPath);
public:
    DatabaseManager database;

    CartRepository cart;
    OrderRepository order;
    ProductRepository product;
    ReceiptRepository receipt;
    ReviewRepository review;
    UserRepository user;
    WishRepository wish;

    RepositoryProvider(const std::string& databasePath = "sportwear.db", const std::string& schemaPath = "schema.sql");

    bool isDatabaseReady() const {return databaseReady;}
};
