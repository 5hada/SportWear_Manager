#pragma once

#include <QWidget>
#include <qtmetamacros.h>

using std::string;

class ElaLineEdit;
class ElaPushButton;
class ElaText;

class FormWidget: public QWidget {
    Q_OBJECT
    
    ElaLineEdit* topEdit;
    ElaLineEdit* bottomEdit;
    ElaPushButton* leftButton;
    ElaPushButton* rightButton;

    ElaText* title;
    ElaText* desc;
    ElaText* topEditText;
    ElaText* bottomEditText;
    ElaText* leftButtonText;
    ElaText* rightButtonText;

    void initLayout();
    void initConnect();
public:
    FormWidget(QWidget* parent = nullptr);

    void setMainText(string title, string desc = NULL);
    void setEditText(string topEditText, string bottomEditText);
    void setButtonText(string leftButtonText, string rightButtonText);

Q_SIGNALS:
    void leftButtonClicked();
    void rightButtonClicked(string topInput, string bottomInput);
};