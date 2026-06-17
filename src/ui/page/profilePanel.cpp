#include "profilePanel.h"

#include "profile/userPanel.h"
#include "profile/signupPanel.h"
#include "profile/loginPanel.h"
#include "profile/logoutPanel.h"

#include <QStackedWidget>

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
    layouts = new QStackedWidget();
    userPanel = new UserPanel();
    signupPanel = new SignupPanel();
    loginPanel = new LoginPanel();
    logoutPanel = new LogoutPanel();

    layouts->addWidget(userPanel);
    layouts->addWidget(signupPanel);
    layouts->addWidget(loginPanel);
    layouts->addWidget(logoutPanel);
    layouts->setCurrentWidget(userPanel);

    layouts->currentWidget();
}

void ProfilePanel::show(UserRole role) {
    switch (role) {
        case UserRole::Admin:
            return ;
            
        case UserRole::Guest:
        case UserRole::User:
        return;
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