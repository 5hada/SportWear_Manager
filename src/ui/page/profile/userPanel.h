

#include <QWidget>

class ElaPushButton;

class UserPanel: public QWidget {
    ElaPushButton* signupButton;
    ElaPushButton* loginButton;
    ElaPushButton* logoutButton;

public:
    explicit UserPanel(QWidget* parent = nullptr);

};