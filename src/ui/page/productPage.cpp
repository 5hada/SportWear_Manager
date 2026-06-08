#include "productPage.h"

#include <QLabel>
#include <QVBoxLayout>

ProductPage::ProductPage(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Product List", this));
    setLayout(layout);
}
