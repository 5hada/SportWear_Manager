#pragma once

#include <ElaWidgetTools/ElaScrollPage.h>

class ElaLineEdit;
class ElaPushButton;
class ElaText;

class LoginPage : public ElaScrollPage{
    Q_OBJECT

    ElaLineEdit* idEdit{nullptr};
    ElaLineEdit* passwordEdit{nullptr};
    ElaPushButton* loginButton{nullptr};

    
    ElaText* titleText{nullptr};
    ElaText* descText{nullptr};
    ElaText* statusText{nullptr};
public:
    explicit LoginPage(QWidget* parent = nullptr);
    ~LoginPage() override;

    void setStatus(const QString& status);

Q_SIGNALS:
    void loginRequested(const QString& name, const QString& password);
};
