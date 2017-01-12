#ifndef WRITEMACHCAMCONFIGFILEXML
#define WRITEMACHCAMCONFIGFILEXML

//WriteXML
//CHS 23/10/2015

//Copy and then fill in this document. Run it and it generate the right xml config file for the machine concerned,

#include <QtCore>
#include <QtXml/QDomDocument>
#include <QDebug>

    //Camera Types so far...........
    //FS_LOCAL_CAM
    //FS_SISO_CIS_RGB
    //FS_SISO_CIS_GRAY
    //FS_BASLER_DART_PYLON_AREA
    //FS_TDALSA_GIGE_LINE_GRAY

    bool writeMachCamConfigFileXML();

#endif // WRITEMACHCAMCONFIGFILEXML

