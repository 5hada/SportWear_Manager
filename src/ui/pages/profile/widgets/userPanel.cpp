#include "userPanel.h"
#include <ElaText.h>
#include <ElaPushButton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>

UserPanel::UserPanel(QWidget* parent): QWidget(parent) {
    titleText = new ElaText("Guest", this);
    titleText->setTextPixelSize(26);

    descText = new ElaText("Choose an account action.", this);
    descText->setTextPixelSize(15);

    signupButton = new ElaPushButton("Sign Up", this);
    loginButton = new ElaPushButton("Login", this);
    logoutButton = new ElaPushButton("Logout", this);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(signupButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(loginButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(logoutButton);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(32, 28, 32, 28);
    mainLayout->setSpacing(14);
    mainLayout->addWidget(titleText);
    mainLayout->addWidget(descText);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    connect(signupButton, &ElaPushButton::clicked, this, &UserPanel::signupRequested);
    connect(loginButton, &ElaPushButton::clicked, this, &UserPanel::loginRequested);
    connect(logoutButton, &ElaPushButton::clicked, this, &UserPanel::logoutRequested);
}

void UserPanel::setRole(const UserRole& role) {
    switch (role) {
        case UserRole::Guest:
            titleText->setText("Welcome, Guest!");
            signupButton->setVisible(true);
            loginButton->setVisible(true);
            logoutButton->setVisible(false);
            break;
        case UserRole::User:
            titleText->setText("Welcome, User!");
            signupButton->setVisible(false);
            loginButton->setVisible(false);
            logoutButton->setVisible(true);
            break;
        case UserRole::Admin:
            titleText->setText("Welcome, Admin!");
            signupButton->setVisible(false);
            loginButton->setVisible(false);
            logoutButton->setVisible(true);
            break;
    }
}