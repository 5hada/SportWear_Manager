#include "loginPage.h"

#include <QPushButton>
#include <QFormLayout>

LoginPage::LoginPage(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Login", this));
    layout->addWidget(new QLineEdit(this));
    layout->addWidget(new QLineEdit(this));
    layout->addWidget(new QPushButton("Sign in", this));
    setLayout(layout);
}

void LoginPage::buildInterface() {
    auto *loginTab = new QWidget(tab);
    auto *loginLayout = new QFormLayout(loginTab);
    usernameEdit = new QLineEdit("user", loginTab);
    passwordEdit = new QLineEdit("1234", loginTab);
    passwordEdit->setEchoMode(QLineEdit::Password);
    auto *loginButton = new QPushButton("Sign in", loginTab);
    loginLayout->addRow("ID", usernameEdit);
    loginLayout->addRow("Password", passwordEdit);
    loginLayout->addRow(loginButton);
}
