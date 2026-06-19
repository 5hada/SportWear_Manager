#pragma once

#include <ElaScrollPage.h>

#include "model/product/product.h"
#include "model/review.h"
#include "model/user/user.h"

class ElaPlainTextEdit;
class ElaText;
class ElaPushButton;
class ElaSpinBox;
class ElaTableView;
class QStandardItemModel;
class QWidget;

class ProductDetailPage : public ElaScrollPage {
    Q_OBJECT

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
    int currentUserId{0};
    UserRole currentUserRole{UserRole::Guest};
    bool canWriteReview{false};
    int editingReviewId{0};
    int selectedCount;

    void initPage();
    void refresh();
    void refreshReviews();
    void resetReviewEditor();
    void beginReviewEdit(const Review& review);

public:
    explicit ProductDetailPage(QWidget* parent): ElaScrollPage(parent) {initPage();}
    ~ProductDetailPage() override = default;

    void setProduct(const Product& product, bool wished = false);
    void setReviewContext(int userId, UserRole role, bool canWrite);
    void setReviews(const Reviews& reviews);
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
