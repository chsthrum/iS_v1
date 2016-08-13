//qt includes
#include <QDesktopWidget>
//local includes
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //set the scroll area
    scrollArea = new QScrollArea;
    widget = new Widget;
    //make the widget a child of the scroll area
    scrollArea->setWidget(widget);
    //make the scroll area the central widget
    this->setCentralWidget(scrollArea);
    //set the centralWidget to the size here under
    resize(QDesktopWidget().availableGeometry(this).size() * 0.9);
}

MainWindow::~MainWindow()
{

}
