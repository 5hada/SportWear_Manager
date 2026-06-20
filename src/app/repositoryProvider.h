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

using std::string;

class RepositoryProvider {
    bool databaseReady = false;


    void seedProducts();

    static string resolveSchemaPath(const string& schemaPath);
public:
    DatabaseManager database;

    CartRepository cart;
    OrderRepository order;
    ProductRepository product;
    ReceiptRepository receipt;
    ReviewRepository review;
    UserRepository user;
    WishRepository wish;

    RepositoryProvider(const string& databasePath = "sportwear.db", const string& schemaPath = "schema.sql");

    bool isDatabaseReady() const {return databaseReady;}
};
