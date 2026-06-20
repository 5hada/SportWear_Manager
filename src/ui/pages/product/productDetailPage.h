#pragma once

#include <ElaScrollPage.h>

#include "model/ui/productPageContent.h"
#include "model/ui/reviewContent.h"

#include <string>
#include <vector>

class ElaPlainTextEdit;
class ElaText;
class ElaIconButton;
class ElaPushButton;
class ElaSpinBox;
class ElaTableView;
class QStandardItemModel;
class QWidget;

class ProductDetailPage : public ElaScrollPage {
    Q_OBJECT

    struct ReviewRowWidget {
        ReviewRow review;
        int reviewId = -1;

        QWidget* actions{nullptr};
        ElaPushButton* editButton{nullptr};
        ElaPushButton* deleteButton{nullptr};
    };

    ProductDetailContent product;
    std::vector<ReviewRow> reviews;

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
    ElaIconButton* addCartButton{nullptr};
    ElaPushButton* editButton{nullptr};

    bool canWriteReview = false;
    bool cartAvailable = true;
    bool wishAvailable = true;

    std::string reviewSummary{"No reviews yet."};
    std::vector<ReviewRowWidget> reviewRows;
    int editingReviewId = 0;

    void initWindow();
    void initLayout();

    void refresh();
    void refreshReviews();
    void ensureReviewRows(int count);
    void clearReviewRow(int row);
    void resetReviewEditor();
    void beginReviewEdit(const ReviewRow& review);

public:
    explicit ProductDetailPage(QWidget* parent);

    void setContent(const ProductDetailContent& content);
    void setReviewContent(const ReviewContent& content);
    void setAdminMode(bool isAdmin);
    void setCartAvailable(bool isAvailable);
    void setWishAvailable(bool isAvailable);

Q_SIGNALS:
    void backRequest();
    void orderRequest(int productId, int count = 1);
    void cartRequest(int productId, int count = 1);
    void wishRequest(int productId, bool isWished);
    void editRequest(int productId);
    void reviewSaveRequested(int reviewId, int productId, int rating, const QString& comment);
    void reviewDeleteRequested(int reviewId);
};
