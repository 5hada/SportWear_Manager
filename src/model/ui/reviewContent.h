#pragma once

#include "model/review.h"

#include <string>
#include <vector>

struct ProductReviewContent {
    Reviews reviews;
    std::string summary{"No reviews yet."};
    std::vector<int> manageableReviewIds;
    bool canWrite{false};
};
