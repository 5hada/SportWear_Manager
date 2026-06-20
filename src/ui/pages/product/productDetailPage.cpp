#include "productDetailPage.h"
#include "ElaDef.h"
#include "ElaIconButton.h"
#include "ui/common/tableItemUtil.h"

#include <ElaPlainTextEdit.h>
#include <ElaPushButton.h>
#include <ElaSpinBox.h>
#include <ElaTableView.h>
#include <ElaText.h>
#include <algorithm>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QWidget>
#include <qboxlayout.h>


void ProductDetailPage::initPage() {
    setWindowTitle("Product Detail");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    auto* backButton = new ElaIconButton(ElaIconType::AngleLeft, this);
    backButton->setFixedSize(40, 40);

    auto* titleText = new ElaText("Product Detail", this);
    titleText->setTextPixelSize(35);

    auto* titleRow = new QHBoxLayout();
    titleRow->setSpacing(12);
    titleRow->addWidget(backButton);
    titleRow->addWidget(titleText);
    titleRow->addStretch();
    editButton = new ElaPushButton("Edit", this);
    editButton->setFixedSize(90, 34);
    editButton->hide();
    titleRow->addWidget(editButton);

    nameText = new ElaText(this);
    nameText->setTextPixelSize(24);

    priceText = new ElaText(this);
    priceText->setTextPixelSize(18);

    stockText = new ElaText(this);
    stockText->setTextPixelSize(18);

    detailText = new ElaText(this);
    detailText->setTextPixelSize(15);
    detailText->setWordWrap(true);

    auto* textLayout = new QVBoxLayout();
    textLayout->setSpacing(14);
    textLayout->addLayout(titleRow);
    textLayout->addSpacing(12);
    textLayout->addWidget(nameText);
    textLayout->addWidget(priceText);
    textLayout->addWidget(stockText);
    textLayout->addWidget(detailText);

    auto* addCartButton = new ElaIconButton(ElaIconType::CartShopping, this);
    wishButton = new ElaPushButton("Add Wish", this);
    auto* buyButton = new ElaPushButton("Buy Now", this);
    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    buttonLayout->addWidget(wishButton);
    buttonLayout->addWidget(addCartButton);
    buttonLayout->addWidget(buyButton);
    buttonLayout->addStretch();

    auto* reviewTitleText = new ElaText("Reviews", this);
    reviewTitleText->setTextPixelSize(22);
    reviewSummaryText = new ElaText("No reviews yet.", this);
    reviewSummaryText->setTextPixelSize(14);

    reviewEditor = new QWidget(this);
    auto* reviewEditorLayout = new QVBoxLayout(reviewEditor);
    reviewEditorLayout->setContentsMargins(0, 0, 0, 0);
    reviewEditorLayout->setSpacing(8);

    auto* reviewInputRow = new QHBoxLayout();
    auto* ratingLabel = new ElaText("Rating", this);
    ratingLabel->setTextPixelSize(14);
    reviewRatingSpin = new ElaSpinBox(this);
    reviewRatingSpin->setRange(1, 5);
    reviewRatingSpin->setValue(5);
    reviewRatingSpin->setFixedSize(100, 34);
    reviewInputRow->addWidget(ratingLabel);
    reviewInputRow->addWidget(reviewRatingSpin);
    reviewInputRow->addStretch();

    reviewCommentEdit = new ElaPlainTextEdit(this);
    reviewCommentEdit->setPlaceholderText("Write a review.");
    reviewCommentEdit->setFixedHeight(80);

    reviewSubmitButton = new ElaPushButton("Add Review", this);
    reviewSubmitButton->setFixedSize(120, 34);
    reviewCancelButton = new ElaPushButton("Cancel", this);
    reviewCancelButton->setFixedSize(100, 34);
    reviewCancelButton->hide();
    auto* reviewButtonRow = new QHBoxLayout();
    reviewButtonRow->addStretch();
    reviewButtonRow->addWidget(reviewCancelButton);
    reviewButtonRow->addSpacing(8);
    reviewButtonRow->addWidget(reviewSubmitButton);

    reviewEditorLayout->addLayout(reviewInputRow);
    reviewEditorLayout->addWidget(reviewCommentEdit);
    reviewEditorLayout->addLayout(reviewButtonRow);

    reviewModel = new QStandardItemModel(this);
    reviewModel->setHorizontalHeaderLabels({"Rating", "User", "Comment", "Actions"});
    centerHeaderItems(reviewModel);

    reviewTable = new ElaTableView(this);
    reviewTable->setModel(reviewModel);
    reviewTable->setAlternatingRowColors(true);
    reviewTable->verticalHeader()->setHidden(true);
    reviewTable->horizontalHeader()->setStretchLastSection(true);
    reviewTable->setSelectionMode(QAbstractItemView::NoSelection);
    reviewTable->setFixedHeight(220);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Product Detail");

    auto* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(30, 20, 30, 20);
    mainLayout->addLayout(textLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(24);
    mainLayout->addWidget(reviewTitleText);
    mainLayout->addWidget(reviewSummaryText);
    mainLayout->addWidget(reviewEditor);
    mainLayout->addWidget(reviewTable);
    mainLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);

    connect(backButton, &ElaIconButton::clicked, this, &ProductDetailPage::backRequest);
    connect(editButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT editRequest(product.getId());
    });
    connect(addCartButton, &ElaIconButton::clicked, this, [this]() {
        Q_EMIT cartRequest(product.getId());
    });
    connect(wishButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT wishRequest(product.getId(), !wished);
    });
    connect(buyButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT orderRequest(product.getId(), 1);
    });
    connect(reviewSubmitButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT reviewSaveRequested(
            editingReviewId,
            product.getId(),
            reviewRatingSpin->value(),
            reviewCommentEdit->toPlainText()
        );
    });
    connect(reviewCancelButton, &ElaPushButton::clicked, this, [this]() {
        resetReviewEditor();
    });
    refresh();
}

void ProductDetailPage::setProduct(const Product& product, bool wished) {
    this->product = product;
    this->wished = wished;
    reviews.clear();
    resetReviewEditor();
    refresh();
}

void ProductDetailPage::setReviewContent(const ProductReviewContent& content) {
    canWriteReview = content.canWrite;
    reviews = content.reviews;
    reviewSummary = content.summary;
    manageableReviewIds = content.manageableReviewIds;
    resetReviewEditor();
    refreshReviews();
}

void ProductDetailPage::setAdminMode(bool isAdmin) {
    if (editButton != nullptr) {
        editButton->setVisible(isAdmin);
    }
}

void ProductDetailPage::refresh() {
    nameText->setText(product.getName().empty() ?
        "Unknown" : QString::fromStdString(product.getName()));
    priceText->setText(QString("Price: %1").arg(product.getPrice()));
    stockText->setText(QString("Stock: %1").arg(product.getStock()));
    detailText->setText(product.getDetail().empty() ?
        "No detail." : QString::fromStdString(product.getDetail()));
    if (wishButton != nullptr) {
        wishButton->setText(wished ? "Remove Wish" : "Add Wish");
    }
    if (reviewEditor != nullptr) {
        reviewEditor->setVisible(canWriteReview);
    }
    refreshReviews();
}

void ProductDetailPage::refreshReviews() {
    if (reviewModel == nullptr || reviewSummaryText == nullptr) {
        return;
    }

    ensureReviewRows(static_cast<int>(reviews.size()));
    for (int row = 0; row < static_cast<int>(reviewRows.size()); ++row) {
        clearReviewRow(row);
    }

    if (reviews.empty()) {
        reviewSummaryText->setText(QString::fromStdString(reviewSummary));
    }
    else {
        int rowIndex = 0;
        for (const auto& review : reviews) {
            reviewTable->setRowHidden(rowIndex, false);
            reviewModel->item(rowIndex, 0)->setText(QString("%1 / 5").arg(review.getRating()));
            reviewModel->item(rowIndex, 1)->setText(QString("User %1").arg(review.getUserId()));
            reviewModel->item(rowIndex, 2)->setText(QString::fromStdString(review.getComment()));
            reviewRows[rowIndex].review = review;
            reviewRows[rowIndex].reviewId = review.getId();
            const bool canManage = std::find(manageableReviewIds.begin(), manageableReviewIds.end(), review.getId()) != manageableReviewIds.end();
            reviewRows[rowIndex].actions->setVisible(canManage);
            reviewRows[rowIndex].editButton->setVisible(canManage);
            reviewRows[rowIndex].deleteButton->setVisible(canManage);
            ++rowIndex;
        }
        reviewSummaryText->setText(QString::fromStdString(reviewSummary));
    }

    reviewTable->resizeColumnsToContents();
    reviewTable->setColumnWidth(0, 90);
    reviewTable->setColumnWidth(1, 90);
    reviewTable->setColumnWidth(3, 170);
}

void ProductDetailPage::ensureReviewRows(int count) {
    while (reviewModel->rowCount() < count) {
        QList<QStandardItem*> row;
        row << centeredItem();
        row << centeredItem();
        row << centeredItem();
        row << centeredItem();
        reviewModel->appendRow(row);

        const int rowIndex = reviewModel->rowCount() - 1;
        auto* editReviewButton = new ElaPushButton("Edit", reviewTable);
        editReviewButton->setFixedSize(68, 28);
        auto* deleteReviewButton = new ElaPushButton("Delete", reviewTable);
        deleteReviewButton->setFixedSize(78, 28);
        auto* actions = new QWidget(reviewTable);
        auto* actionsLayout = new QHBoxLayout(actions);
        actionsLayout->setContentsMargins(0, 0, 0, 0);
        actionsLayout->setSpacing(6);
        actionsLayout->addStretch();
        actionsLayout->addWidget(editReviewButton);
        actionsLayout->addWidget(deleteReviewButton);
        actionsLayout->addStretch();
        actions->hide();
        reviewTable->setIndexWidget(reviewModel->index(rowIndex, 3), actions);
        editReviewButton->hide();
        deleteReviewButton->hide();
        reviewRows.push_back({actions, editReviewButton, deleteReviewButton, Review{}, -1});

        connect(editReviewButton, &ElaPushButton::clicked, this, [this, rowIndex]() {
            if (reviewRows[rowIndex].reviewId > 0) {
                beginReviewEdit(reviewRows[rowIndex].review);
            }
        });
        connect(deleteReviewButton, &ElaPushButton::clicked, this, [this, rowIndex]() {
            if (reviewRows[rowIndex].reviewId > 0) {
                Q_EMIT reviewDeleteRequested(reviewRows[rowIndex].reviewId);
            }
        });
    }
}

void ProductDetailPage::clearReviewRow(int row) {
    if (row < 0 || row >= reviewModel->rowCount()) {
        return;
    }
    for (int column = 0; column < reviewModel->columnCount(); ++column) {
        reviewModel->item(row, column)->setText("");
    }
    reviewRows[row].reviewId = -1;
    reviewRows[row].actions->hide();
    reviewRows[row].editButton->hide();
    reviewRows[row].deleteButton->hide();
    reviewTable->setRowHidden(row, true);
}

void ProductDetailPage::resetReviewEditor() {
    editingReviewId = 0;
    if (reviewRatingSpin != nullptr) {
        reviewRatingSpin->setValue(5);
    }
    if (reviewCommentEdit != nullptr) {
        reviewCommentEdit->clear();
    }
    if (reviewSubmitButton != nullptr) {
        reviewSubmitButton->setText("Add Review");
    }
    if (reviewCancelButton != nullptr) {
        reviewCancelButton->hide();
    }
    if (reviewEditor != nullptr) {
        reviewEditor->setVisible(canWriteReview);
    }
}

void ProductDetailPage::beginReviewEdit(const Review& review) {
    editingReviewId = review.getId();
    if (reviewEditor != nullptr) {
        reviewEditor->show();
    }
    if (reviewRatingSpin != nullptr) {
        reviewRatingSpin->setValue(review.getRating());
    }
    if (reviewCommentEdit != nullptr) {
        reviewCommentEdit->setPlainText(QString::fromStdString(review.getComment()));
        reviewCommentEdit->setFocus();
    }
    if (reviewSubmitButton != nullptr) {
        reviewSubmitButton->setText("Update Review");
    }
    if (reviewCancelButton != nullptr) {
        reviewCancelButton->show();
    }
}
