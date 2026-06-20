#pragma once

#include <QWidget>
#include "model/user/user.h"

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
    void setRole(const UserRole& role = UserRole::Guest);

Q_SIGNALS:
    void signupRequested();
    void loginRequested();
    void logoutRequested();
};
