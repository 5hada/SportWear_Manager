#pragma once

#include<QBoxLayout>

class ElaLineEdit;
class ElaPushButton;
class ElaText;


class FormPanelLayout: public QBoxLayout{
    Q_OBJECT

    ElaLineEdit* idEdit{nullptr};
    ElaLineEdit* passwordEdit{nullptr};
    ElaPushButton* loginButton{nullptr};
    ElaText* statusText{nullptr};
public:

};