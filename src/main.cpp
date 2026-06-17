#include "app/appContext.h"
#include "ui/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <ElaApplication.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ElaApplication::getInstance()->init();

    AppContext app;

    MainWindow window(app.adminController, app.authController, app.cartController, app.orderController, app.productController);
    window.show();

    return a.exec();
}