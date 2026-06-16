#pragma once

#include <string>
#include <array>

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

std::string categoryToString(Category category);
Category categoryFromString(const std::string& value);
