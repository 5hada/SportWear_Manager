#include "cartPage.h"

#include <QLabel>
#include <QVBoxLayout>

CartPage::CartPage(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Cart", this));
    setLayout(layout);
}
