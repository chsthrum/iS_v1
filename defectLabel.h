#ifndef DEFECTLABEL_H
#define DEFECTLABEL_H
//qt includes
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>


class DefectLabel : public QLabel
{
    Q_OBJECT

public:    
     DefectLabel(QWidget *parent = 0);
    ~DefectLabel();

protected:
    void mousePressEvent(QMouseEvent *ev);

signals:

public slots:
};

#endif // DEFECTLABEL_H
