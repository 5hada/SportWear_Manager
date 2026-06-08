#include "reviewPage.h"

#include <QLabel>
#include <QVBoxLayout>

ReviewPage::ReviewPage(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Reviews", this));
    setLayout(layout);
}
