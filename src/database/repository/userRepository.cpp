#include "userRepository.h"

namespace {
std::string columnText(sqlite3_stmt* statement, int column)
{
    const auto* text = sqlite3_column_text(statement, column);
    return text == nullptr ? std::string() : reinterpret_cast<const char*>(text);
}
}

UserRepository::UserRepository(DataBaseManager* database)
    : database(database)
{
    if (!hasDatabase()) {
        save(User(1, "admin", "0000", 0));
    }
}

void UserRepository::setDatabase(DataBaseManager* database)
{
    this->database = database;
}

const std::vector<User>& UserRepository::findAll() const
{
    if (!hasDatabase()) {
        return users;
    }

    users.clear();
    constexpr auto sql = "SELECT id, name, password, point FROM users ORDER BY id";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return users;
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {
        users.push_back(userFromStatement(statement));
    }
    sqlite3_finalize(statement);
    return users;
}

std::optional<User> UserRepository::findById(int id) const
{
    if (!hasDatabase()) {
        for (const auto& user : users) {
            if (user.getId() == id) {
                return user;
            }
        }
        return std::nullopt;
    }

    constexpr auto sql = "SELECT id, name, password, point FROM users WHERE id = ?";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }

    sqlite3_bind_int(statement, 1, id);
    std::optional<User> result;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        result = userFromStatement(statement);
    }
    sqlite3_finalize(statement);
    return result;
}

std::optional<User> UserRepository::findByName(const std::string& name) const
{
    if (!hasDatabase()) {
        for (const auto& user : users) {
            if (user.getName() == name) {
                return user;
            }
        }
        return std::nullopt;
    }

    constexpr auto sql = "SELECT id, name, password, point FROM users WHERE name = ?";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }

    sqlite3_bind_text(statement, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    std::optional<User> result;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        result = userFromStatement(statement);
    }
    sqlite3_finalize(statement);
    return result;
}

void UserRepository::save(const User& user)
{
    if (!hasDatabase()) {
        for (auto& stored : users) {
            if (stored.getId() == user.getId()) {
                stored = user;
                return;
            }
        }
        users.push_back(user);
        return;
    }

    constexpr auto sql =
        "INSERT INTO users (id, name, password, point) VALUES (?, ?, ?, ?) "
        "ON CONFLICT(id) DO UPDATE SET name = excluded.name, password = excluded.password, point = excluded.point";
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database->handle(), sql, -1, &statement, nullptr) != SQLITE_OK) {
        return;
    }

    sqlite3_bind_int(statement, 1, user.getId());
    sqlite3_bind_text(statement, 2, user.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, user.getPassword().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 4, user.getPoint());
    sqlite3_step(statement);
    sqlite3_finalize(statement);
}

bool UserRepository::hasDatabase() const
{
    return database != nullptr && database->isOpen();
}

User UserRepository::userFromStatement(sqlite3_stmt* statement)
{
    return User(
        sqlite3_column_int(statement, 0),
        columnText(statement, 1),
        columnText(statement, 2),
        sqlite3_column_int(statement, 3));
}
