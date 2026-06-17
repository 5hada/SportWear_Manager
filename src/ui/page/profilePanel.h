
#include "model/user/user.h"
#include <ElaDialog.h>

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

    void initPanel();
    void initLayout();

    void setUser();
    void setSignup();
    void setLogin();
    void setLogout();
public:
    explicit ProfilePanel(QWidget* parent = nullptr);

    void show(UserRole role);
};