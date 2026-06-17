#pragma once

#include <QWidget>

class ElaPushButton;
class ElaText;

class LogoutPanel: public QWidget {
    ElaText* titleText{nullptr};
    ElaText* descText{nullptr};
    ElaPushButton* cancelButton{nullptr};
    ElaPushButton* logoutButton{nullptr};

public:
    explicit LogoutPanel(QWidget* parent = nullptr);
};
