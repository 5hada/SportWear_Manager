
#include "ElaDialog.h"
#include <functional>

class ElaText;
class ElaPushButton;

enum class DialogCallback {
    Signup,
    Login,
    Logout,
    Unknown
};


class Dialog: public ElaDialog {
    Q_OBJECT

    DialogCallback callback;

    ElaText* title;
    ElaText* desc;
    ElaText* state;

    ElaPushButton* leftButton{nullptr};
    ElaPushButton* rightButton{nullptr};

    std::function<void()> onConfirm;

    void initLayout();
    void setTitle(std::string title);
    void setDesc(std::string desc);
    void setState(std::string state);
    void setLeftButtonText(std::string text);
    void setRightButtonText(std::string text);

public:
    Dialog(QWidget* parent = nullptr);

    void setPanel();
    void setUserPanel();

    void setAlert();
    void setLogoutAlert();
    void setConfirm();
    void setOrderConfirm();
    void setNotice();
    void setErrorNotice();
    void setOrderNotice();

    void setForm();
    void setLoginForm();
    void setSignupForm();

Q_SIGNALS:
    void leftClicked();
    void rightClicked();

    void loginRequested();
};