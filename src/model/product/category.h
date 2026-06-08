#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

enum class Category {
    Unknown,
    Top,
    Bottom,
    Shoes,
    Accessory
};

std::string categoryToString(Category category);

#endif // CATEGORY_H
