#pragma once

#include <string>
#include <array>

using std::string;

enum class Category {
    Unknown,
    Top,
    Bottom,
    Shoes,
    Accessory
};

constexpr std::array Categories{
    Category::Unknown,
    Category::Top,
    Category::Bottom,
    Category::Shoes,
    Category::Accessory
};

string categoryToString(Category category);
Category categoryFromString(const string& value);
