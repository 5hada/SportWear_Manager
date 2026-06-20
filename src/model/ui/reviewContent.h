#pragma once

#include <string>
#include <vector>
#include <utility>

using std::vector;
using std::string;

struct ReviewRow {
    int id = -1;
    int userId = -1;
    int rating = 0;
    string comment;
    bool canManage = false;

    ReviewRow() = default;
    ReviewRow(int id, int userId, int rating, string comment, bool canManage = false):
        id(id), userId(userId), rating(rating), comment(std::move(comment)), canManage(canManage) {}
};

struct ReviewContent {
    vector<ReviewRow> rows;
    string summary{"No reviews yet."};
    bool canWrite = false;

    ReviewContent& operator<<(const ReviewRow& row) {
        rows.push_back(row);
        return *this;
    }
};
