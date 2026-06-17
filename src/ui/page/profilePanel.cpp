#include "profilePanel.h"

#include "profile/userPanel.h"
#include "profile/signupPanel.h"
#include "profile/loginPanel.h"
#include "profile/logoutPanel.h"

#include <QStackedWidget>
#include <QString>
#include <QVBoxLayout>

ProfilePanel::ProfilePanel(QWidget* parent): ElaDialog(parent) {
    initPanel();
    initLayout();
}

void ProfilePanel::initPanel() {
    setFixedSize(600, 400);
    setAppBarHeight(0);
    this->setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);
}

void ProfilePanel::initLayout() {
    layouts = new QStackedWidget(this);
    userPanel = new UserPanel(this);
    signupPanel = new SignupPanel(this);
    loginPanel = new LoginPanel(this);
    logoutPanel = new LogoutPanel(this);

    layouts->addWidget(userPanel);
    layouts->addWidget(signupPanel);
    layouts->addWidget(loginPanel);
    layouts->addWidget(logoutPanel);
    layouts->setCurrentWidget(userPanel);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(layouts);
}

void ProfilePanel::show(UserRole role) {
    switch (role) {
        case UserRole::Admin:
            break;
        case UserRole::Guest:
            break;
        case UserRole::User:
            break;
    }
}

void ProfilePanel::setUser() {
    layouts->setCurrentWidget(signupPanel);
}

void ProfilePanel::setSignup() {
    layouts->setCurrentWidget(signupPanel);
}

void ProfilePanel::setLogin() {
    layouts->setCurrentWidget(loginPanel);
}

void ProfilePanel::setLogout() {
    layouts->setCurrentWidget(logoutPanel);
}
