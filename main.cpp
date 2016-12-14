//qt includes
#include <QApplication>
//local includes
#include "mainwindow.h"
#include  "xmlStuff/writemachcamconfigfilexml.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!writeMachCamConfigFileXML())
        std::cout << " did not write XML file" << std::endl;
    MainWindow w;
    w.show();


    return a.exec();
}
