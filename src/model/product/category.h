#pragma once

#include <string>

enum class Category {
    Unknown,
    Top,
    Bottom,
    Shoes,
    Accessory
};

std::string categoryToString(Category category);