#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "addstuwin.h"
#include <QObject>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication app(argc, argv);
    MainWindow *mywin = new MainWindow(0);

    mywin->show();


    return app.exec();
}
