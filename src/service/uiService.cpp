#include "uiService.h"

#include "service/productService.h"

#include <algorithm>
#include <sstream>

void UiService::setProductService(ProductService* productService) {
    this->productService = productService;
}

int UiService::pageMaxIndex(int totalCount, int pageSize) const {
    if (pageSize <= 0 || totalCount <= 0) {
        return 0;
    }
    return (totalCount - 1) / pageSize;
}

ProductGridPageContent UiService::makeProductGridPageContent(const Products& products, int currentPage, int maxPage) const {
    ProductGridPageContent content(PageNavigationContent(currentPage, maxPage));
    for (const auto& product : products) {
        content << ProductCardContent(
            product.getId(),
            product.getName(),
            categoryToString(product.getCategory()),
            product.getPrice(),
            product.getStock(),
            product.getDetail().empty() ? "No detail." : product.getDetail()
        );
    }
    return content;
}

ProductDetailContent UiService::makeProductDetailContent(const Product& product, bool wished) const {
    return ProductDetailContent(
        product.getId(),
        product.getName(),
        categoryToString(product.getCategory()),
        product.getPrice(),
        product.getStock(),
        product.getDetail().empty() ? "No detail." : product.getDetail(),
        wished
    );
}

ProductFormContent UiService::makeProductFormContent(const Product& product) const {
    return ProductFormContent(
        product.getId(),
        product.getName(),
        product.getCategory(),
        product.getPrice(),
        product.getStock(),
        product.getDetail()
    );
}

OrderPanelContent UiService::makeOrderPanelContent(const Order& order, int payment) const {
    OrderPanelContent content;
    for (const auto& item : order.getItems()) {
        content << OrderRowContent(item.id, item.count, item.price);
    }
    content.totalPrice = order.getTotalPrice();
    content.availablePoints = order.getAvailablePoints();
    content.maxUsablePoint = std::min(order.getAvailablePoints(), order.getTotalPrice());
    content.payment = payment;
    return content;
}

CartWidgetContent UiService::makeCartWidgetContent(const Cart& cart) const {
    CartWidgetContent content;
    for (const auto& item : cart.getItems()) {
        content << CartWidgetRowContent(item.id, item.count, item.price);
    }
    return content;
}

CartPageContent UiService::makeCartPageContent(const Cart& cart, int currentPage, int pageSize) const {
    const int maxPage = pageMaxIndex(static_cast<int>(cart.getItems().size()), pageSize);
    CartPageContent content(PageNavigationContent(currentPage, maxPage));
    for (const auto& item : cart.getItems()) {
        if (item.isSelected()) {
            content.totalCount += item.count;
            content.totalPrice += item.count * item.price;
        }
    }

    const int begin = currentPage * pageSize;
    const int end = std::min(begin + pageSize, static_cast<int>(cart.getItems().size()));
    for (int index = begin; index < end; ++index) {
        const auto& item = cart.getItems()[index];
        std::string productName = "Unknown";
        if (productService != nullptr) {
            const auto product = productService->getById(item.id);
            if (!product.getName().empty()) {
                productName = product.getName();
            }
        }
        content << CartRowContent(item.id, productName, item.count, item.price, item.isSelected());
    }
    return content;
}

ReceiptPageContent UiService::makeReceiptPageContent(const Receipts& receipts, int currentPage, int pageSize) const {
    const int maxPage = pageMaxIndex(static_cast<int>(receipts.size()), pageSize);
    ReceiptPageContent content(PageNavigationContent(currentPage, maxPage));

    const int begin = currentPage * pageSize;
    const int end = std::min(begin + pageSize, static_cast<int>(receipts.size()));
    for (int index = begin; index < end; ++index) {
        content << ReceiptRowContent(
            receipts[index].getId(),
            receipts[index].getDate(),
            getReceiptItemSummary(receipts[index]),
            receipts[index].getPaid(),
            receipts[index].getIsCanceled()
        );
    }
    return content;
}

WishPageContent UiService::makeWishPageContent(const Products& wishs, int currentPage, int pageSize) const {
    const int maxPage = pageMaxIndex(static_cast<int>(wishs.size()), pageSize);
    WishPageContent content(PageNavigationContent(currentPage, maxPage));

    const int begin = currentPage * pageSize;
    const int end = std::min(begin + pageSize, static_cast<int>(wishs.size()));
    for (int index = begin; index < end; ++index) {
        content << WishRowContent(
            wishs[index].getId(),
            wishs[index].getName(),
            wishs[index].getPrice(),
            wishs[index].getStock()
        );
    }
    return content;
}

ReviewContent UiService::makeReviewContent(const Reviews& reviews, const std::vector<int>& manageableReviewIds, bool canWrite) const {
    ReviewContent content;
    content.canWrite = canWrite;
    content.summary = getReviewSummary(reviews);
    for (const auto& review : reviews) {
        const bool canManage = std::find(manageableReviewIds.begin(), manageableReviewIds.end(), review.getId()) != manageableReviewIds.end();
        content << ReviewRow(
            review.getId(),
            review.getUserId(),
            review.getRating(),
            review.getComment(),
            canManage
        );
    }
    return content;
}

std::string UiService::getReceiptItemSummary(const Receipt& receipt) const {
    const auto items = receipt.getOrderItems();
    if (items.empty()) {
        return "No items";
    }

    int quantity = 0;
    for (const auto& item : items) {
        quantity += item.count;
    }

    const auto& first = items.front();
    std::ostringstream out;
    out << "Product #" << first.id << " x" << first.count;
    if (items.size() > 1) {
        out << " + " << (items.size() - 1) << " more";
    }
    out << " (" << quantity << " total)";
    return out.str();
}

std::string UiService::getReviewSummary(const Reviews& reviews) const {
    if (reviews.empty()) {
        return "No reviews yet.";
    }

    int ratingSum = 0;
    for (const auto& review : reviews) {
        ratingSum += review.getRating();
    }
    const double average = static_cast<double>(ratingSum) / static_cast<double>(reviews.size());

    std::ostringstream out;
    out.setf(std::ios::fixed);
    out.precision(1);
    out << reviews.size() << " reviews - Average " << average << " / 5";
    return out.str();
}
