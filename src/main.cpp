#include <QtSingleApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QtSingleApplication app(argc, argv);

    if (app.isRunning())
        return 0;

    MainWindow mw;

    app.setActivationWindow(&mw);

    //mw.show();
    return app.exec();
}
