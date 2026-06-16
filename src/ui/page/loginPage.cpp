#include "loginPage.h"

#include <ElaLineEdit.h>
#include <ElaPushButton.h>
#include <ElaText.h>
#include <QFormLayout>
#include <QVBoxLayout>

LoginPage::LoginPage(QWidget* parent): ElaScrollPage(parent) {
    setWindowTitle("Login");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);

    titleText = new ElaText("Login", this);
    titleText->setTextPixelSize(35);

    descText = new ElaText("Sign in to manage products, wish lists, and orders.", this);
    descText->setTextPixelSize(16);

    idEdit = new ElaLineEdit(this);
    idEdit->setPlaceholderText("User ID");
    idEdit->setFixedWidth(320);

    passwordEdit = new ElaLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setFixedWidth(320);

    loginButton = new ElaPushButton("Login", this);
    loginButton->setFixedWidth(140);

    statusText = new ElaText("Enter your account information.", this);
    statusText->setTextPixelSize(14);

    connect(loginButton, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT loginRequested(idEdit->text(), passwordEdit->text());
    });

    auto* formLayout = new QFormLayout();
    formLayout->setContentsMargins(30, 10, 0, 0);
    formLayout->setHorizontalSpacing(18);
    formLayout->setVerticalSpacing(14);
    formLayout->addRow("ID", idEdit);
    formLayout->addRow("Password", passwordEdit);
    formLayout->addRow("", loginButton);

    auto* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Login");

    auto* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(30, 20, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(16);
    centerLayout->addLayout(formLayout);
    centerLayout->addSpacing(8);
    centerLayout->addWidget(statusText);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, false, 0);
}

LoginPage::~LoginPage() = default;

void LoginPage::setStatus(const QString& status) {
    statusText->setText(status);
}
