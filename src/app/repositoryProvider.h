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
#include <filesystem>
#include <array>
#include <set>

class RepositoryProvider {
public:
    DatabaseManager database;

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
        databaseReady = database.initialize(databasePath, resolveSchemaPath(schemaPath));
        seedProducts();
    }

    bool isDatabaseReady() const { return databaseReady; }

private:
    static std::string resolveSchemaPath(const std::string& schemaPath) {
        namespace fs = std::filesystem;
        const fs::path requested(schemaPath);
        if (fs::exists(requested)) {
            return requested.string();
        }

        const fs::path sourceTreeSchema = fs::path("src") / "database" / "schema.sql";
        if (fs::exists(sourceTreeSchema)) {
            return sourceTreeSchema.string();
        }

        const fs::path parentSourceTreeSchema = fs::path("..") / "src" / "database" / "schema.sql";
        if (fs::exists(parentSourceTreeSchema)) {
            return parentSourceTreeSchema.string();
        }

        return schemaPath;
    }

    void seedProducts() {
        if (!databaseReady) {
            return;
        }

        constexpr int targetProductCount = 240;
        const auto existingProducts = product.findAll();
        if (static_cast<int>(existingProducts.size()) >= targetProductCount) {
            return;
        }

        std::set<std::string> existingNames;
        for (const auto& existingProduct : existingProducts) {
            existingNames.insert(existingProduct.getName());
        }

        struct CategorySeed {
            Category category;
            std::array<const char*, 4> names;
            int basePrice;
        };

        constexpr std::array<CategorySeed, 4> categorySeeds{{
            {Category::Top, {"Training Tee", "Compression Top", "Running Jacket", "Yoga Tank"}, 24000},
            {Category::Bottom, {"Running Shorts", "Training Pants", "Compression Tights", "Track Joggers"}, 32000},
            {Category::Shoes, {"Court Shoes", "Trail Runners", "Training Sneakers", "Recovery Slides"}, 58000},
            {Category::Accessory, {"Gym Bag", "Sports Cap", "Wrist Wraps", "Performance Socks"}, 12000},
        }};
        constexpr std::array<const char*, 15> variants{
            "Essential", "Core", "Pro", "Elite", "Aero",
            "Flex", "Dry", "Thermal", "Light", "Power",
            "Urban", "Endurance", "Studio", "Outdoor", "Recovery"
        };

        int inserted = 0;
        for (int index = 0;
             static_cast<int>(existingProducts.size()) + inserted < targetProductCount
             && index < targetProductCount * 2;
             ++index) {
            const auto& categorySeed = categorySeeds[index % categorySeeds.size()];
            const int nameIndex = (index / static_cast<int>(categorySeeds.size())) % categorySeed.names.size();
            const int variantIndex = (index / static_cast<int>(categorySeeds.size() * categorySeed.names.size())) % variants.size();

            const std::string name =
                std::string(variants[variantIndex]) + " " + categorySeed.names[nameIndex];
            if (existingNames.find(name) != existingNames.end()) {
                continue;
            }

            const int stock = 8 + (index * 7) % 65;
            const int price = categorySeed.basePrice + nameIndex * 7000 + variantIndex * 1200;
            Product seededProduct(Item{0, stock, price}, name, categorySeed.category);
            seededProduct.setDetail(
                "Seed product for sportwear UI testing: " +
                categoryToString(categorySeed.category) +
                " / " +
                variants[variantIndex]
            );
            if (product.insert(seededProduct)) {
                existingNames.insert(name);
                ++inserted;
            }
        }
    }
    bool databaseReady = false;
};
