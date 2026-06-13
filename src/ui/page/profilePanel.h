
#include<ElaDialog.h>



class QStackedWidget;

class ProfilePanel: public ElaDialog{
    Q_OBJECT

    QStackedWidget* widgets{nullptr};
    std::string name;
    bool isLoggedIn;

public:
    explicit ProfilePanel(QWidget* parent = nullptr);
    ~ProfilePanel();


    void initPanel();
};