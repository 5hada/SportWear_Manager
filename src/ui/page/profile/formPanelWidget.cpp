#include"formPanelWidget.h"
#include "ElaDef.h"
#include "ElaDialog.h"
#include "ElaLineEdit.h"
#include "ElaText.h"
#include<QString>
#include<ElaPushButton.h>
#include<QFormLayout>



FormPanelWidget::FormPanelWidget(QWidget* parent): ElaDialog(parent){
    initLayout();
}
FormPanelWidget::~FormPanelWidget() = default;


void FormPanelWidget::initLayout() {
    setWindowTitle("Profile");
    setWindowIcon(QIcon(":/include/Image/Moon.jpg"));
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);
    ElaText* titleText = new ElaText();
    titleText->setText("Login");
    titleText->setTextPixelSize(35);

    ElaText* descText = new ElaText();
    descText->setText("Please enter your account.");
    descText->setTextPixelSize(16);

    idEdit = new ElaLineEdit();
    idEdit->setPlaceholderText("User ID");
    idEdit->setFixedWidth(320);

    passwordEdit = new ElaLineEdit();
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setFixedWidth(320);

    button1 = new ElaPushButton("Login");

    connect(button1, &ElaPushButton::clicked, this, [this]() {
        Q_EMIT loginRequested(idEdit->text(), passwordEdit->text());
    });

    auto* formLayout = new QFormLayout();
    formLayout->setContentsMargins(30, 10, 0, 0);
    formLayout->setHorizontalSpacing(18);
    formLayout->setVerticalSpacing(14);
    formLayout->addRow("ID", idEdit);
    formLayout->addRow("Password", passwordEdit);
    formLayout->addRow("", button1);

    auto* centerLayout = new QVBoxLayout(this);
    centerLayout->setContentsMargins(30, 0, 30, 20);
    centerLayout->setSpacing(12);
    centerLayout->addWidget(titleText);
    centerLayout->addWidget(descText);
    centerLayout->addSpacing(16);
    centerLayout->addLayout(formLayout);
    centerLayout->addSpacing(8);
    centerLayout->addStretch();
}