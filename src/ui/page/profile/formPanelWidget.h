#pragma once

#include "ElaDialog.h"
#include<QBoxLayout>
#include <QWidget>

class ElaLineEdit;
class ElaPushButton;


class FormPanelWidget: public ElaDialog{
    Q_OBJECT

    ElaLineEdit* idEdit{nullptr};
    ElaLineEdit* passwordEdit{nullptr};
    ElaPushButton* button1{nullptr};
public:
    explicit FormPanelWidget(QWidget* parent = nullptr);
    ~FormPanelWidget() override;

    void initLayout();

Q_SIGNALS:
    void loginRequested(const QString& name, const QString& password);
};