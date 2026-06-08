#include "category.h"

std::string categoryToString(Category category)
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
