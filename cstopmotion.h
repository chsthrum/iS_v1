#ifndef CSTOPMOTION_H
#define CSTOPMOTION_H

//qt includes
#include <QWidget>

//local includes
#include "ImagingStuff/Structures.h"


class CstopMotion : public QWidget
{
    Q_OBJECT
public:
    explicit CstopMotion(QWidget *parent = 0);
    ~CstopMotion();

private:
    QList<DefectStructToSave> defectImageCollection;
    QList<DefectStructToSave> imminentDefectsCollection;


signals:

public slots:
};

#endif // CSTOPMOTION_H

