//qt includes
#include <QApplication>
//local includes
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int x = 4;

    int* testInt = new int;
    testInt = &x;


    MainWindow w;
    w.show();

    return a.exec();
}
