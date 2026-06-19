
#include"formWidget.h"

class LoginPanel: public FormWidget {

    void initLayout();
    void initConnect();
public:
    explicit LoginPanel(QWidget* parent = nullptr);
};