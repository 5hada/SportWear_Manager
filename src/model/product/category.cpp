#include "category.h"

std::string categoryToString(Category category) {
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

Category categoryFromString(const std::string& value) {
    if (value == "Top") {
        return Category::Top;
    }
    if (value == "Bottom") {
        return Category::Bottom;
    }
    if (value == "Shoes") {
        return Category::Shoes;
    }
    if (value == "Accessory") {
        return Category::Accessory;
    }
    return Category::Unknown;
}
