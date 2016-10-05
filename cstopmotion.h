#ifndef CSTOPMOTION_H
#define CSTOPMOTION_H

//qt includes
#include <QWidget>

//local includes
#include "ImagingStuff/Structures.h"
#include "ImagingStuff/Config.h"
#include "defectimagestorage.h"


class CstopMotion : public QWidget
{
    Q_OBJECT
public:

    explicit CstopMotion(QWidget *parent, int nCams);
    //explicit CstopMotion(QWidget *parent = 0);
    //explicit CameraWidget(QWidget *parent, int deviceNumber, int nDefectImages, SharedImageBuffer *sharedImageBuffer);
    ~CstopMotion();

private:
    QList<DefectStructToSave> defectImageCollection;
    QList<DefectStructToSave> imminentDefectsCollection;
    QList<int>nStopDistanceOffsets;
    int numberOfCameras;



signals:

public slots:
};

#endif // CSTOPMOTION_H

