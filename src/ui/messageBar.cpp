#include "messageBar.h"

#include "ElaMessageBar.h"
#include <qwidget.h>


namespace MessageBar {
    void Success(QWidget* parent){
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success!", "", 3000, parent);
    }
    void Fail(QWidget* parent){
        ElaMessageBar::error(ElaMessageBarType::BottomRight, "Failed!", "", 3000, parent);
    }

    void Loigin(QWidget* parent){
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "Logged in", "", 3000, parent);
    }
    void Logout(QWidget* parent){
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "Logged out", "", 3000, parent);
    }
    void Signup(QWidget* parent){
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "Signed up", "proceed to login", 3000, parent);
    }
}