#pragma once

#include <ElaScrollPage.h>
#include <vector>

#include "model/product/product.h"

class ElaTableView;
class QStandardItemModel;

class WishPage : public ElaScrollPage
{
    Q_OBJECT

public:
    explicit WishPage(QWidget* parent = nullptr);
    ~WishPage() override;

    void setWishProducts(std::vector<Product> products);

private:
    void rebuildRows();

    ElaTableView* wishTable{nullptr};
    QStandardItemModel* model{nullptr};
    std::vector<Product> wishProducts;
};
