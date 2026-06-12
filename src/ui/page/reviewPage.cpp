#include "reviewPage.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ReviewPage::ReviewPage(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Reviews", this));
    setLayout(layout);
}

void ReviewPage::buildInterface() {
    auto *reviewTab = new QWidget(tab);
    auto *reviewLayout = new QVBoxLayout(reviewTab);
    reviewRatingSpin = new QSpinBox(reviewTab);
    reviewRatingSpin->setRange(1, 5);
    reviewCommentEdit = new QLineEdit(reviewTab);
    reviewCommentEdit->setPlaceholderText("Review comment for selected product");
    auto *reviewButton = new QPushButton("Write review", reviewTab);
    reviewList = new QListWidget(reviewTab);
    reviewLayout->addWidget(new QLabel("Select a product in Product tab first", reviewTab));
    reviewLayout->addWidget(reviewRatingSpin);
    reviewLayout->addWidget(reviewCommentEdit);
    reviewLayout->addWidget(reviewButton);
    reviewLayout->addWidget(reviewList);
}

void ReviewPage::refreshReviews() {
    reviewList->clear();
    const int productId = selectedProductId();
    if (productId == 0) {
        return;
    }

    for (const auto &review : app.services.review.reviewsForProduct(productId)) {
        reviewList->addItem(QString::number(review.rating()) + "/5 | "
                             + QString::fromStdString(review.comment()));
    }
}
