#include "loginPanel.h"


LoginPanel::LoginPanel(QWidget* parent): FormWidget(parent) {
    initLayout();
    initConnect();
}

void LoginPanel::initLayout() {
    setMainText("Login", "login to get more advantages");
    setEditText("ID", "Password");
    setButtonText("Cancel", "Submit");
}

void LoginPanel::initConnect() {
    
}