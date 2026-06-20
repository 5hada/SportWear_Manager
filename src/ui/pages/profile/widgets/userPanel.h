#pragma once

#include <QWidget>
#include "model/ui/userInfo.h"

class ElaPushButton;
class ElaText;

class UserPanel: public QWidget {
    Q_OBJECT

    ElaText* titleText{nullptr};
    ElaText* descText{nullptr};
    ElaPushButton* signupButton;
    ElaPushButton* loginButton;
    ElaPushButton* logoutButton;

public:
    explicit UserPanel(QWidget* parent = nullptr);
    void setUser(const UserInfo& user = UserInfo());

Q_SIGNALS:
    void signupRequested();
    void loginRequested();
    void logoutRequested();
};
