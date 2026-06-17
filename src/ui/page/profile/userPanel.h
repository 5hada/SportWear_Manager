#pragma once

#include <QWidget>

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

Q_SIGNALS:
    void signupRequested();
    void loginRequested();
    void logoutRequested();
};
