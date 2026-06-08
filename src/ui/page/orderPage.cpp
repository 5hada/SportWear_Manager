#include "orderPage.h"

#include <QLabel>
#include <QVBoxLayout>

OrderPage::OrderPage(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Orders", this));
    setLayout(layout);
}
