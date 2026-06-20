#include "reviewRepository.h"

using std::nullopt;

Reviews ReviewRepository::findAll() const {
    Reviews reviews{};
    if (hasDatabase()) {
        constexpr auto sql =
            "SELECT id, user_id, product_id, rating, comment FROM reviews ORDER BY id";
        sqlite3_stmt* statement = nullptr;
        if (sqlOk(sql, statement)) {
            while (sqlite3_step(statement) == SQLITE_ROW) {
                reviews.push_back(reviewFromStatement(statement));
            }
            sqlite3_finalize(statement);
        }

    }
    return reviews;
}

optional<Review> ReviewRepository::findById(int id) const {
    if (!hasDatabase()) {return nullopt;}

    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "SELECT id, user_id, product_id, rating, comment FROM reviews WHERE id = ?";
    if (!sqlOk(sql, statement)) {
        return nullopt;
    }

    optional<Review> review = nullopt;
    sqlite3_bind_int(statement, 1, id);
    if (sqlite3_step(statement) == SQLITE_ROW) {
        review = reviewFromStatement(statement);
    }
    sqlite3_finalize(statement);
    return review;
}

Reviews ReviewRepository::findByProductId(int productId) const {
    Reviews reviews{};
    if (!hasDatabase()) {return reviews;}

    Reviews result;
    constexpr auto sql =
        "SELECT id, user_id, product_id, rating, comment FROM reviews WHERE product_id = ? ORDER BY id";
    sqlite3_stmt* statement = nullptr;
    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, productId);
        while (sqlite3_step(statement) == SQLITE_ROW) {
            result.push_back(reviewFromStatement(statement));
        }
        sqlite3_finalize(statement);
    }
    return result;
}

Reviews ReviewRepository::findByUser(int userId) const {
    Reviews reviews{};
    if (!hasDatabase()) {return reviews;}

    Reviews result;
    constexpr auto sql =
        "SELECT id, user_id, product_id, rating, comment FROM reviews WHERE user_id = ? ORDER BY id";
    sqlite3_stmt* statement = nullptr;
    if (sqlOk(sql, statement)) {
        sqlite3_bind_int(statement, 1, userId);
        while (sqlite3_step(statement) == SQLITE_ROW) {
            result.push_back(reviewFromStatement(statement));
        }
        sqlite3_finalize(statement);
    }
    return result;
}

bool ReviewRepository::insert(const Review& review) {
    if (!hasDatabase()) {return false;}

    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "INSERT INTO reviews (user_id, product_id, rating, comment) VALUES (?, ?, ?, ?)";
    if (!sqlOk(sql, statement)) {
        return false;
    }
    sqlite3_bind_int(statement, 1, review.getUserId());
    sqlite3_bind_int(statement, 2, review.getProductId());
    sqlite3_bind_int(statement, 3, review.getRating());
    sqlBindText(statement, 4, review.getComment());
    return sqlFin(statement);
}

bool ReviewRepository::update(const Review& review) {
    if (!hasDatabase()) {return false;}

    sqlite3_stmt* statement = nullptr;
    if (review.getId() < 0) {return false;}
    constexpr auto sql =
        "UPDATE reviews SET rating = ?, comment = ? WHERE id = ? ";
    if (!sqlOk(sql, statement)) {
        return false;
    }
    sqlite3_bind_int(statement, 1, review.getRating());
    sqlBindText(statement, 2, review.getComment());
    sqlite3_bind_int(statement, 3, review.getId());
    return sqlFin(statement);
}

bool ReviewRepository::remove(int id) {
    if (!hasDatabase()) {return false;}

    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "DELETE FROM reviews WHERE id = ?";
    if (!sqlOk(sql, statement)) {
        return false;
    }
    sqlite3_bind_int(statement, 1, id);
    return sqlFin(statement);
}

int ReviewRepository::nextId() const{
    if (!hasDatabase()) {return 0;}

    constexpr auto sql =
        "SELECT COALESCE(MAX(id), 0) + 1 FROM reviews";
    sqlite3_stmt* statement = nullptr;
    if (!sqlOk(sql, statement)) {
        return 1;
    }

    int next = 1;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        next = sqlite3_column_int(statement, 0);
    }
    sqlite3_finalize(statement);
    return next;
}

Review ReviewRepository::reviewFromStatement(sqlite3_stmt* statement) {
    return Review(
        sqlite3_column_int(statement, 0),
        sqlite3_column_int(statement, 1),
        sqlite3_column_int(statement, 2),
        sqlite3_column_int(statement, 3),
        columnText(statement, 4));
}
