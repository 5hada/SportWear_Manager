#pragma once

#include <QWidget>

using std::string;

class ElaLineEdit;
class ElaPushButton;
class ElaText;

class FormWidget: public QWidget {
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
    bool leftButtonClicked();
    bool rightButtonClicked(string topInput, string bottomInput);
};