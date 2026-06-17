#include "signupPanel.h"


SignupPanel::SignupPanel(QWidget* parent): FormWidget(parent) {
    initLayout();
    initConnect();
}

void SignupPanel::initLayout() {
    setMainText("Sign Up", "Resister to get a better experience");
    setEditText("ID", "Password");
    setButtonText("Cancel", "Register");
}

void SignupPanel::initConnect() {

}