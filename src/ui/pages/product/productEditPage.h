#pragma once

#include <ElaScrollPage.h>

#include "model/product/product.h"

class ElaComboBox;
class ElaLineEdit;
class ElaPlainTextEdit;
class ElaSpinBox;
class ElaText;

class ProductEditPage : public ElaScrollPage {
    Q_OBJECT

    Product product;
    ElaText* titleText{nullptr};
    ElaLineEdit* nameEdit{nullptr};
    ElaComboBox* categoryCombo{nullptr};
    ElaSpinBox* priceSpin{nullptr};
    ElaSpinBox* stockSpin{nullptr};
    ElaPlainTextEdit* detailEdit{nullptr};

    void initPage();
    void initLayout();
    void initConnect();
    void setCategory(Category category);
    Category selectedCategory() const;

public:
    explicit ProductEditPage(QWidget* parent = nullptr);

    void setAddMode();
    void setEditMode(const Product& product);

Q_SIGNALS:
    void saveRequested(const Product& product);
    void cancelRequested();
};
