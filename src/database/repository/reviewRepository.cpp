#include "reviewRepository.h"

namespace {
std::string columnText(sqlite3_stmt* statement, int column)
{
    const auto* text = sqlite3_column_text(statement, column);
    return text == nullptr ? std::string() : reinterpret_cast<const char*>(text);
}
}

ReviewRepository::ReviewRepository(DataBaseManager* database)
    : database(database)
{
}

void ReviewRepository::setDatabase(DataBaseManager* database)
{
    this->database = database;
}

const std::vector<Review>& ReviewRepository::findAll() const
{
    if (!hasDatabase()) {
        return reviews;
    }

    reviews.clear();
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

std::vector<Review> ReviewRepository::findByProductId(int productId) const
{
    if (!hasDatabase()) {
        std::vector<Review> result;
        for (const auto& review : reviews) {
            if (review.getProductId() == productId) {
                result.push_back(review);
            }
        }
        return result;
    }

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

void ReviewRepository::save(const Review& review)
{
    if (!hasDatabase()) {
        reviews.push_back(review);
        return;
    }

    sqlite3_stmt* statement = nullptr;
    if (review.getId() > 0) {
        constexpr auto sql =
            "INSERT INTO reviews (id, user_id, product_id, rating, comment) VALUES (?, ?, ?, ?, ?) "
            "ON CONFLICT(id) DO UPDATE SET user_id = excluded.user_id, product_id = excluded.product_id, "
            "rating = excluded.rating, comment = excluded.comment";
        if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
            return;
        }
        sqlite3_bind_int(statement, 1, review.getId());
        sqlite3_bind_int(statement, 2, review.getUserId());
        sqlite3_bind_int(statement, 3, review.getProductId());
        sqlite3_bind_int(statement, 4, review.getRating());
        sqlite3_bind_text(statement, 5, review.getComment().c_str(), -1, SQLITE_TRANSIENT);
    } else {
        constexpr auto sql = "INSERT INTO reviews (user_id, product_id, rating, comment) VALUES (?, ?, ?, ?)";
        if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
            return;
        }
        sqlite3_bind_int(statement, 1, review.getUserId());
        sqlite3_bind_int(statement, 2, review.getProductId());
        sqlite3_bind_int(statement, 3, review.getRating());
        sqlite3_bind_text(statement, 4, review.getComment().c_str(), -1, SQLITE_TRANSIENT);
    }

    sqlite3_step(statement);
    sqlite3_finalize(statement);
}

int ReviewRepository::nextId() const
{
    if (!hasDatabase()) {
        return static_cast<int>(reviews.size()) + 1;
    }

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

bool ReviewRepository::hasDatabase() const
{
    return database != nullptr && database->isOpen();
}

Review ReviewRepository::reviewFromStatement(sqlite3_stmt* statement)
{
    return Review(
        sqlite3_column_int(statement, 0),
        sqlite3_column_int(statement, 1),
        sqlite3_column_int(statement, 2),
        sqlite3_column_int(statement, 3),
        columnText(statement, 4));
}
