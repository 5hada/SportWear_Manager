#pragma once

#include <ElaScrollPage.h>

#include "model/product/product.h"
#include "model/review.h"
#include "model/ui/reviewContent.h"

#include <string>
#include <vector>

class ElaPlainTextEdit;
class ElaText;
class ElaPushButton;
class ElaSpinBox;
class ElaTableView;
class QStandardItemModel;
class QWidget;

class ProductDetailPage : public ElaScrollPage {
    Q_OBJECT

    struct ReviewRowWidgets {
        QWidget* actions{nullptr};
        ElaPushButton* editButton{nullptr};
        ElaPushButton* deleteButton{nullptr};
        Review review;
        int reviewId{-1};
    };

    Product product;
    Reviews reviews;
    ElaText* nameText{nullptr};
    ElaText* priceText{nullptr};
    ElaText* stockText{nullptr};
    ElaText* detailText{nullptr};
    ElaText* reviewSummaryText{nullptr};
    QWidget* reviewEditor{nullptr};
    ElaSpinBox* reviewRatingSpin{nullptr};
    ElaPlainTextEdit* reviewCommentEdit{nullptr};
    ElaPushButton* reviewSubmitButton{nullptr};
    ElaPushButton* reviewCancelButton{nullptr};
    ElaTableView* reviewTable{nullptr};
    QStandardItemModel* reviewModel{nullptr};
    ElaPushButton* wishButton{nullptr};
    ElaPushButton* editButton{nullptr};
    bool wished{false};
    bool canWriteReview{false};
    std::string reviewSummary{"No reviews yet."};
    std::vector<int> manageableReviewIds;
    std::vector<ReviewRowWidgets> reviewRows;
    int editingReviewId{0};
    int selectedCount;

    void initPage();
    void refresh();
    void refreshReviews();
    void ensureReviewRows(int count);
    void clearReviewRow(int row);
    void resetReviewEditor();
    void beginReviewEdit(const Review& review);

public:
    explicit ProductDetailPage(QWidget* parent): ElaScrollPage(parent) {initPage();}
    ~ProductDetailPage() override = default;

    void setProduct(const Product& product, bool wished = false);
    void setReviewContent(const ProductReviewContent& content);
    void setAdminMode(bool isAdmin);

Q_SIGNALS:
    void backRequest();
    void orderRequest(int productId, int count = 1);
    void cartRequest(int productId, int count = 1);
    void wishRequest(int productId, bool isWished);
    void editRequest(int productId);
    void reviewSaveRequested(int reviewId, int productId, int rating, const QString& comment);
    void reviewDeleteRequested(int reviewId);
};
