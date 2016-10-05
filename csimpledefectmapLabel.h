#ifndef CSIMPLEDEFECTMAPLABEL_H
#define CSIMPLEDEFECTMAPLABEL_H

//makes a very samll label to mark the position of the defect tin the stop motion simple map and allows a mouse press event

//qt includes
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>

class CsimpleDefectMapLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CsimpleDefectMapLabel(QWidget *parent = 0);
    ~CsimpleDefectMapLabel();

protected:
    void mousePressEvent(QMouseEvent *ev);

signals:

public slots:
};

#endif // CSIMPLEDEFECTMAPLABEL_H



