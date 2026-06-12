#include "app/appContext.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>

class LoginPage : public QWidget {
    AppContext app;

    QTabWidget *tab = nullptr;
    QLineEdit *usernameEdit = nullptr;
    QLineEdit *passwordEdit = nullptr;
public:
    explicit LoginPage(QWidget *parent = nullptr);
    
    void buildInterface();
    bool requireLogin();
};
