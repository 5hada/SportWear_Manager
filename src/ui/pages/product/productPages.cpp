#include "productPages.h"

#include "productDetailPage.h"
#include "productEditPage.h"
#include "productGridPage.h"

#include <QStackedWidget>
#include <QVBoxLayout>

ProductPages::ProductPages(int itemsPerPage, QWidget* parent): QWidget(parent) {
    initWidgets(itemsPerPage);
    initConnect();
}

void ProductPages::initWidgets(int itemsPerPage) {
    stack = new QStackedWidget(this);
    gridPage = new ProductGridPage(itemsPerPage, this);
    detailPage = new ProductDetailPage(this);
    editPage = new ProductEditPage(this);

    stack->addWidget(gridPage);
    stack->addWidget(detailPage);
    stack->addWidget(editPage);
    stack->setCurrentWidget(gridPage);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(stack);
}

void ProductPages::initConnect() {
    connect(gridPage, &ProductGridPage::productSelected, this, &ProductPages::productSelected);
    connect(gridPage, &ProductGridPage::searchRequested, this, &ProductPages::searchRequested);
    connect(gridPage, &ProductGridPage::categoryChanged, this, &ProductPages::categoryChanged);
    connect(gridPage, &ProductGridPage::pageIndexChanged, this, &ProductPages::pageIndexChanged);
    connect(gridPage, &ProductGridPage::addRequested, this, &ProductPages::addRequested);

    connect(detailPage, &ProductDetailPage::backRequest, this, &ProductPages::backRequested);
    connect(detailPage, &ProductDetailPage::cartRequest, this, &ProductPages::cartRequested);
    connect(detailPage, &ProductDetailPage::orderRequest, this, &ProductPages::orderRequested);
    connect(detailPage, &ProductDetailPage::wishRequest, this, &ProductPages::wishRequested);
    connect(detailPage, &ProductDetailPage::editRequest, this, &ProductPages::editRequested);
    connect(detailPage, &ProductDetailPage::reviewSaveRequested, this, &ProductPages::reviewSaveRequested);
    connect(detailPage, &ProductDetailPage::reviewDeleteRequested, this, &ProductPages::reviewDeleteRequested);

    connect(editPage, &ProductEditPage::saveRequested, this, &ProductPages::productSaveRequested);
    connect(editPage, &ProductEditPage::cancelRequested, this, &ProductPages::productCancelRequested);
}




void ProductPages::showGrid() {
    stack->setCurrentWidget(gridPage);
}

void ProductPages::showDetail() {
    stack->setCurrentWidget(detailPage);
}

void ProductPages::showAddForm() {
    editPage->setAddMode();
    stack->setCurrentWidget(editPage);
}

void ProductPages::showEditForm(const ProductFormContent& content) {
    editPage->setEditMode(content);
    stack->setCurrentWidget(editPage);
}



bool ProductPages::isDetailVisible() const {
    return stack->currentWidget() == detailPage;
}




void ProductPages::setGridCategory(Category category) {
    gridPage->setCategory(category);
}

void ProductPages::setGridContents(const ProductGridPageContent& content) {
    gridPage->setContents(content);
}

void ProductPages::setProductContent(const ProductDetailContent& content) {
    detailPage->setContent(content);
}

void ProductPages::setReviewContent(const ReviewContent& content) {
    detailPage->setReviewContent(content);
}

void ProductPages::setAdminMode(bool isAdmin) {
    gridPage->setAdminMode(isAdmin);
    detailPage->setAdminMode(isAdmin);
}

void ProductPages::setCartAvailable(bool isAvailable) {
    detailPage->setCartAvailable(isAvailable);
}

void ProductPages::setWishAvailable(bool isAvailable) {
    detailPage->setWishAvailable(isAvailable);
}
