#include "loginPage.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

LoginPage::LoginPage(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Login", this));
    layout->addWidget(new QLineEdit(this));
    layout->addWidget(new QLineEdit(this));
    layout->addWidget(new QPushButton("Sign in", this));
    setLayout(layout);
}
