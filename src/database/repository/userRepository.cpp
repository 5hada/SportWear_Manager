#include "userRepository.h"


const std::vector<User> UserRepository::findAll() const {
    std::vector<User> users{};
    if (hasDatabase()) {
        constexpr auto sql = "SELECT id, name, password, point FROM users ORDER BY id";
        sqlite3_stmt* statement = nullptr;
        if (sqlOk(sql, statement)) {
            while (sqlite3_step(statement) == SQLITE_ROW) {
                users.push_back(userFromStatement(statement));
            }
            sqlite3_finalize(statement);
        }
    }
    return users;
}

std::optional<User> UserRepository::findById(int id) const {
    std::optional<User> result;
    if (hasDatabase()) {
        constexpr auto sql = "SELECT id, name, password, point FROM users WHERE id = ?";
        sqlite3_stmt* statement = nullptr;
        if (!sqlOk(sql, statement)) {
            return std::nullopt;
        }

        sqlite3_bind_int(statement, 1, id);
        if (sqlite3_step(statement) == SQLITE_ROW) {
            result = userFromStatement(statement);
        }
        sqlite3_finalize(statement);
    }
    return result;
}

std::optional<User> UserRepository::findByName(const std::string& name) const {
    std::optional<User> result;
    if (hasDatabase()) {
        constexpr auto sql = "SELECT id, name, password, point FROM users WHERE name = ?";
        sqlite3_stmt* statement = nullptr;
        if (!sqlOk(sql, statement)) {
            return std::nullopt;
        }

        sqlBindText(statement, 1, name);
        if (sqlite3_step(statement) == SQLITE_ROW) {
            result = userFromStatement(statement);
        }
        sqlite3_finalize(statement);
    }
    return result;
}

bool UserRepository::insert(const User& user) {
    if (!hasDatabase()) {return false;}
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "INSERT INTO users (name, password, point) VALUES (?, ?, ?)";

    if (!sqlOk(sql, statement)) {
        return false;
    }
    sqlBindText(statement, 1, user.getName());
    sqlBindText(statement, 2, user.getPassword());
    sqlite3_bind_int(statement, 3, user.getPoint());
    return sqlFin(statement);
}

bool UserRepository::updatePoint(const User& user) {
    if (!hasDatabase()) {return false;}
    sqlite3_stmt* statement = nullptr;
    constexpr auto sql =
        "UPDATE users "
        "SET Point = ? "
        "WHERE id = ?";
        
    if (!sqlOk(sql, statement)) {
        return false;
    }
    sqlite3_bind_int(statement, 1, user.getPoint());
    sqlite3_bind_int(statement, 2, user.getId());
    return sqlFin(statement);
}

User UserRepository::userFromStatement(sqlite3_stmt* statement) {
    return User(
        sqlite3_column_int(statement, 0),
        columnText(statement, 1),
        columnText(statement, 2),
        sqlite3_column_int(statement, 3));
}
