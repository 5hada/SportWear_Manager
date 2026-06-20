#include "profilePanel.h"

#include "widgets/userPanel.h"
#include "widgets/signupPanel.h"
#include "widgets/loginPanel.h"
#include "widgets/logoutPanel.h"

#include <QStackedWidget>
#include <QString>
#include <QVBoxLayout>

ProfilePanel::ProfilePanel(QWidget* parent): ElaDialog(parent) {
    initPanel();
    initLayout();
}

void ProfilePanel::initPanel() {
    setFixedSize(600, 400);
    // setAppBarHeight(0);
    this->setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);
}

void ProfilePanel::initLayout() {
    layouts = new QStackedWidget(this);
    userPanel = new UserPanel(this);
    userPanel->setRole(UserRole::Guest);
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

    connect(userPanel, &UserPanel::signupRequested, this, &ProfilePanel::setSignup);
    connect(userPanel, &UserPanel::loginRequested, this, &ProfilePanel::setLogin);
    connect(userPanel, &UserPanel::logoutRequested, this, &ProfilePanel::setLogout);

    connect(signupPanel, &SignupPanel::leftButtonClicked, this, &ProfilePanel::setUser);
    connect(signupPanel, &SignupPanel::rightButtonClicked, this,
            [this](const string& name, const string& password) {
                emit trySignup(QString::fromStdString(name), QString::fromStdString(password));
            });

    connect(loginPanel, &LoginPanel::leftButtonClicked, this, &ProfilePanel::setUser);
    connect(loginPanel, &LoginPanel::rightButtonClicked, this,
            [this](const string& name, const string& password) {
                emit tryLogin(QString::fromStdString(name), QString::fromStdString(password));
            });

    connect(logoutPanel, &LogoutPanel::cancelRequested, this, &ProfilePanel::setUser);
    connect(logoutPanel, &LogoutPanel::logoutRequested, this, &ProfilePanel::tryLogout);
}

void ProfilePanel::show(UserRole role) {
    currentRole = role;
    setUser();
    ElaDialog::show();
}

void ProfilePanel::setUser() {
    userPanel->setRole(currentRole);
    layouts->setCurrentWidget(userPanel);
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
