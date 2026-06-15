#include "reviewRepository.h"

namespace {
std::string columnText(sqlite3_stmt* statement, int column) {
    const auto* text = sqlite3_column_text(statement, column);
    return text == nullptr ? std::string() : reinterpret_cast<const char*>(text);
}
}


std::vector<Review> ReviewRepository::findAll() const {
    std::vector<Review> reviews{};
    if (!hasDatabase()) {return reviews;}
    
    constexpr auto sql = "SELECT id, user_id, product_id, rating, comment FROM reviews ORDER BY id";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return reviews;
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {
        reviews.push_back(reviewFromStatement(statement));
    }
    sqlite3_finalize(statement);
    return reviews;
}

std::vector<Review> ReviewRepository::findByProductId(int productId) const {
    std::vector<Review> reviews{};
    if (!hasDatabase()) {return reviews;}

    std::vector<Review> result;
    constexpr auto sql = "SELECT id, user_id, product_id, rating, comment FROM reviews WHERE product_id = ? ORDER BY id";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return result;
    }

    sqlite3_bind_int(statement, 1, productId);
    while (sqlite3_step(statement) == SQLITE_ROW) {
        result.push_back(reviewFromStatement(statement));
    }
    sqlite3_finalize(statement);
    return result;
}

std::vector<Review> ReviewRepository::findByUser(int userId) const {
    std::vector<Review> reviews{};
    if (!hasDatabase()) {return reviews;}

    std::vector<Review> result;
    constexpr auto sql = "SELECT id, user_id, product_id, rating, comment FROM reviews WHERE user_id = ? ORDER BY id";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return result;
    }

    sqlite3_bind_int(statement, 1, userId);
    while (sqlite3_step(statement) == SQLITE_ROW) {
        result.push_back(reviewFromStatement(statement));
    }
    sqlite3_finalize(statement);
    return result;
}

bool ReviewRepository::insert(const Review& review) {
    if (!hasDatabase()) {return false;}

    sqlite3_stmt* statement = nullptr;
    constexpr auto sql = "INSERT INTO reviews (user_id, product_id, rating, comment) VALUES (?, ?, ?, ?)";
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(statement, 1, review.getUserId());
    sqlite3_bind_int(statement, 2, review.getProductId());
    sqlite3_bind_int(statement, 3, review.getRating());
    sqlite3_bind_text(statement, 4, review.getComment().c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(statement);
    sqlite3_finalize(statement);
    return true;
}

bool ReviewRepository::update(const Review& review) {
    if (!hasDatabase()) {return false;}

    sqlite3_stmt* statement = nullptr;
    if (review.getId() < 0) {return false;}
    constexpr auto sql =
        "UPDATE reviews SET comment = ? WHERE id = ? ";
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(statement, 1, review.getId());
    sqlite3_bind_text(statement, 2, review.getComment().c_str(), -1, SQLITE_TRANSIENT);
    
    sqlite3_step(statement);
    sqlite3_finalize(statement);
    return true;
}

int ReviewRepository::nextId() const{
    if (!hasDatabase()) {return 0;}

    constexpr auto sql = "SELECT COALESCE(MAX(id), 0) + 1 FROM reviews";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return 1;
    }

    int next = 1;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        next = sqlite3_column_int(statement, 0);
    }
    sqlite3_finalize(statement);
    return next;
}

bool ReviewRepository::hasDatabase() const {
    return database != nullptr && database->isOpen();
}

Review ReviewRepository::reviewFromStatement(sqlite3_stmt* statement) {
    return Review(
        sqlite3_column_int(statement, 0),
        sqlite3_column_int(statement, 1),
        sqlite3_column_int(statement, 2),
        sqlite3_column_int(statement, 3),
        columnText(statement, 4));
}
