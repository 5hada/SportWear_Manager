
#include "ElaDialog.h"

class ElaText;
class ElaPushButton;



class Dialog: public ElaDialog {
    Q_OBJECT

    ElaText* title;
    ElaText* desc;
    ElaText* state;

    ElaPushButton* leftButton{nullptr};
    ElaPushButton* rightButton{nullptr};

    void onCancelClicked();
    void onExitClicked();
public:
    Dialog(QWidget* parent = nullptr) {initLayout();}

    void initLayout();
    void setTitle(std::string title);
    void setDesc(std::string desc);
    void setState(std::string state);
    void setLeftButtonText(std::string text);
    void setRightButtonText(std::string text);

    void setAlert();
    void setLogoutAlert();
    void setConfirm();
    void setOrderConfirm();
    void setNotice();
    void setErrorNotice();
    void setOrderNotice();


Q_SIGNALS:
    void rightClicked();
};