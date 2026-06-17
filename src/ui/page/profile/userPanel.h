#pragma once

#include <QWidget>

class ElaPushButton;
class ElaText;

class UserPanel: public QWidget {
    ElaText* titleText{nullptr};
    ElaText* descText{nullptr};
    ElaPushButton* signupButton;
    ElaPushButton* loginButton;
    ElaPushButton* logoutButton;

public:
    explicit UserPanel(QWidget* parent = nullptr);

};
