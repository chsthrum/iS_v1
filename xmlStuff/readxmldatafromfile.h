#ifndef READXMLDATAFROMFILE
#define READXMLDATAFROMFILE

#include <QtCore>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QVector>


#include "../ImagingStuff/Structures.h"


//takes an xml file and returns a vector of MachCamConfigFileXMLData
//CHS 12/12/16

QVector<MachCamConfigFileXMLData> readXMLDataFromFile(QString);

//check for a dupicate string
bool checkForDuplicateSerialNumber(QVector<MachCamConfigFileXMLData>&);



#endif // READXMLDATAFROMFILE

