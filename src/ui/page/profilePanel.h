
#include<ElaDialog.h>

#include"model/user/sessionInfo.h"

class ProfilePanel: public ElaDialog{
    Q_OBJECT

    std::string name;
    bool isLoggedIn;

public:
    explicit ProfilePanel(QWidget* parent = nullptr);
    ~ProfilePanel();


    void initPanel();
    void defaultPanelConfig();

    void updateUser(SessionInfo info);
};