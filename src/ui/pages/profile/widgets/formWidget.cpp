#include "formWidget.h"
#include "ElaText.h"

#include <ElaLineEdit.h>
#include <ElaPushButton.h>
#include <qboxlayout.h>


FormWidget::FormWidget(QWidget* parent): QWidget(parent) {
    initLayout();
    initConnect();
}

void FormWidget::initLayout() {
    title = new ElaText("Form");
    title->setTextPixelSize(20);
    desc = new ElaText("Description.\nDescribing description");
    desc->setTextPixelSize(14);
    topEditText = new ElaText("Enter the text");
    topEditText->setTextPixelSize(14);
    bottomEditText = new ElaText("Enter the text");
    bottomEditText->setTextPixelSize(14);
    leftButtonText = new ElaText("Cancel");
    rightButtonText = new ElaText("Confirm");
    topEdit = new ElaLineEdit();
    bottomEdit = new ElaLineEdit(); 
    bottomEdit->setEchoMode(QLineEdit::Password);
    leftButton = new ElaPushButton();
    rightButton = new ElaPushButton();

    auto* textLayout = new QVBoxLayout();
    textLayout->addWidget(title);
    textLayout->addSpacing(10);
    textLayout->addWidget(desc);

    auto* editLayout = new QVBoxLayout();
    editLayout->addWidget(topEditText);
    editLayout->addWidget(topEdit);
    editLayout->addSpacing(10);
    editLayout->addWidget(bottomEditText);
    editLayout->addWidget(bottomEdit);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(leftButton);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(rightButton);

    auto* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(20, 10, 20, 10);
    mainLayout->addLayout(textLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(editLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void FormWidget::initConnect() {
    connect(leftButton, &ElaPushButton::clicked, this, [this]() {
        emit leftButtonClicked();
        topEdit->clear();
        bottomEdit->clear();
    });
    connect(rightButton, &ElaPushButton::clicked, this, [this]() {
        emit rightButtonClicked(topEdit->text().toStdString(), bottomEdit->text().toStdString());
        topEdit->clear();
        bottomEdit->clear();
    });
}

void FormWidget::setMainText(string title, string desc) {
    this->title->setText(title.c_str());
    this->desc->setText(desc.c_str());
}

void FormWidget::setEditText(string topEditText, string bottomEditText) {
    this->topEditText->setText(topEditText.c_str());
    this->bottomEditText->setText(bottomEditText.c_str());
}

void FormWidget::setButtonText(string leftButtonText, string rightButtonText) {
    this->leftButtonText->setText(leftButtonText.c_str());
    this->rightButtonText->setText(rightButtonText.c_str());
    leftButton->setText(leftButtonText.c_str());
    rightButton->setText(rightButtonText.c_str());
}
