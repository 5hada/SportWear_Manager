
#include"formWidget.h"


class SignupPanel: public FormWidget {
    void initLayout();
    void initConnect();
public:
    explicit SignupPanel(QWidget* parent = nullptr);

};