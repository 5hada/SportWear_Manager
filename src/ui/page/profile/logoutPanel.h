#pragma once

#include <QWidget>

class ElaPushButton;
class ElaText;

class LogoutPanel: public QWidget {
    Q_OBJECT

    ElaText* titleText{nullptr};
    ElaText* descText{nullptr};
    ElaPushButton* cancelButton{nullptr};
    ElaPushButton* logoutButton{nullptr};

public:
    explicit LogoutPanel(QWidget* parent = nullptr);

Q_SIGNALS:
    void cancelRequested();
    void logoutRequested();
};
