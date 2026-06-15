
#include "ElaDialog.h"

class ElaPushButton;


class AlertDialog: public ElaDialog{
    Q_OBJECT

    ElaPushButton* cancelButton{nullptr};
    ElaPushButton* exitButton{nullptr};

    void onCancelClicked();
    void onExitClicked();
public:
    AlertDialog(QWidget* parent = nullptr);

Q_SIGNALS:
    void exitClicked();
};