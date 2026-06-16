
#include"dialog.h"
#include<ElaPushButton.h>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<ElaText.h>


void Dialog::initLayout() {
    resize(400,200);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);

    title = new ElaText("");
    title->setTextPixelSize(32);
    desc = new ElaText("");
    desc->setTextPixelSize(18);
    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(title);
    textLayout->addWidget(desc);
    
    leftButton = new ElaPushButton();
    rightButton = new ElaPushButton();
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(rightButton);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(textLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    
    setLayout(mainLayout);
    
    connect(leftButton, &ElaPushButton::pressed, this, &Dialog::close);
    connect(rightButton, &ElaPushButton::pressed, this, 
        [=](void){emit rightClicked(); close();});
}

void Dialog::setTitle(std::string title) {
    this->title = new ElaText(title.c_str());
}

void Dialog::setDesc(std::string desc) {
    this->desc = new ElaText(desc.c_str());
}

void Dialog::setState(std::string state) {
    this->state = new ElaText(state.c_str());
}

void Dialog::setLeftButtonText(std::string text) {
    leftButton->setText(text.c_str());
}

void Dialog::setRightButtonText(std::string text) {
    rightButton->setText(text.c_str());
}


void Dialog::setAlert() {
    setWindowTitle("Alert");
    leftButton->setVisible(true);
    rightButton->setVisible(true);
    leftButton->setText("Cancel");
    rightButton->setText("Continue");

}

void Dialog::setConfirm() {
    setWindowTitle("Confirm");
    leftButton->setVisible(true);
    rightButton->setVisible(true);
    leftButton->setText("Cancel");
    rightButton->setText("Confirm");

}

void Dialog::setNotice() {
    setWindowTitle("Notice");
    leftButton->setVisible(false);
    rightButton->setText("Check");
}

void Dialog::setLogoutAlert() {
    setWindowTitle("Logout");
    setAlert();
    leftButton->setText("Cancel");
    rightButton->setText("Logout");

    title->setText("Logout");
    desc->setText("really want to logout?\ncant canceled.");
}

void Dialog::setOrderConfirm() {
    setWindowTitle("Order");
    setConfirm();
    leftButton->setText("Cancel");
    rightButton->setText("Purchase");
}

void Dialog::setOrderNotice() {
    setWindowTitle("Order");
    setNotice();
}

void Dialog::setErrorNotice() {
    setWindowTitle("Error");
    setNotice();
}