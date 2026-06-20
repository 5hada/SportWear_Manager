#pragma once

#include <QWidget>

#include "model/product/category.h"
#include "model/product/product.h"
#include "model/ui/productPageContent.h"
#include "model/ui/reviewContent.h"

#include <string>

class ProductDetailPage;
class ProductEditPage;
class ProductGridPage;
class QStackedWidget;

class ProductPages : public QWidget {
    Q_OBJECT

    QStackedWidget* stack{nullptr};
    ProductGridPage* gridPage{nullptr};
    ProductDetailPage* detailPage{nullptr};
    ProductEditPage* editPage{nullptr};


    void initWidgets(int itemsPerpage);
    void initConnect();

public:
    ProductPages(int itemsPerPage, QWidget* parent = nullptr);

    void showGrid();
    void showDetail();
    void showAddForm();
    void showEditForm(const Product& product);
    bool isDetailVisible() const;

    void setGridCategory(Category category);
    void setGridContents(const ProductGridPageContent& content);
    void setProduct(const Product& product, bool wished);
    void setReviewContent(const ReviewContent& content);
    void setAdminMode(bool isAdmin);

Q_SIGNALS:
    void productSelected(int productId);

    void searchRequested(const std::string& keyword);
    void categoryChanged(Category category);
    void pageIndexChanged(int pageIndex);

    void addRequested();

    void backRequested();
    void cartRequested(int productId);
    void orderRequested(int productId, int count);
    void wishRequested(int productId, bool isWished);
    void editRequested(int productId);

    void reviewSaveRequested(int reviewId, int productId, int rating, const QString& comment);
    void reviewDeleteRequested(int reviewId);
    
    void productSaveRequested(int productId, const QString& name, Category category, int price, int stock, const QString& detail);
    void productCancelRequested();
};
