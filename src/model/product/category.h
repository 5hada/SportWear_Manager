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

inline std::string categoryToString(Category category)
{
    switch (category) {
    case Category::Top:
        return "Top";
    case Category::Bottom:
        return "Bottom";
    case Category::Shoes:
        return "Shoes";
    case Category::Accessory:
        return "Accessory";
    default:
        return "Unknown";
    }
}

#endif // CATEGORY_H
