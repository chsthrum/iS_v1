#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Holds the scrollable main page on which all the camera displays fit

//qt includes
#include <QMainWindow>
#include <QObject>
#include <QScrollArea>
//local includes
#include "cameraContainer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QScrollArea* scrollArea;
    CameraContainer* widget;

};

#endif // MAINWINDOW_H
