#pragma once

#include "model/ui/userInfo.h"
#include <ElaDialog.h>

using std::string;

class QString;

class QStackedWidget;
class UserPanel;
class SignupPanel;
class LoginPanel;
class LogoutPanel;

class ProfilePanel: public ElaDialog{
    Q_OBJECT

    QStackedWidget* layouts{nullptr};
    UserPanel* userPanel;
    SignupPanel* signupPanel;
    LoginPanel* loginPanel;
    LogoutPanel* logoutPanel;
    UserInfo currentUser;

    void initPanel();
    void initLayout();

    void setUser();
    void setSignup();
    void setLogin();
    void setLogout();
public:
    explicit ProfilePanel(QWidget* parent = nullptr);

    void show(const UserInfo& user);
     
Q_SIGNALS:
    void trySignup(const QString& name, const QString& password);
    void tryLogin(const QString& name, const QString& password);
    void tryLogout();
};
