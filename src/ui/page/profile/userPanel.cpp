#include "userPanel.h"
#include <ElaText.h>
#include <ElaPushButton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>

UserPanel::UserPanel(QWidget* parent): QWidget(parent) {
    titleText = new ElaText("User", this);
    titleText->setTextPixelSize(26);

    descText = new ElaText("Choose an account action.", this);
    descText->setTextPixelSize(15);

    signupButton = new ElaPushButton("Sign Up", this);
    loginButton = new ElaPushButton("Login", this);
    logoutButton = new ElaPushButton("Logout", this);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(signupButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(loginButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(logoutButton);
    buttonLayout->addStretch();

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
