#include "app/appContext.h"
#include "ui/mainwindow.h"

#include <QApplication>
#include <QSplashScreen>

#include <ElaApplication.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSplashScreen splash;
    splash.setPixmap(QPixmap(":/images/loading.png"));
    splash.show();
    ElaApplication::getInstance()->init();

    AppContext context;

    MainWindow window(context.event);
    window.show();

    splash.finish(&window);

    return app.exec();
}