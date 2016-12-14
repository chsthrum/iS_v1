//WriteXML
//CHS 23/10/2015

#include "writemachcamconfigfilexml.h"

bool writeMachCamConfigFileXML()
{
    //Camera Types
    //FS_LOCAL_CAM
    //FS_SISO_CIS_RGB
    //FS_SISO_CIS_GRAY
    //FS_BASLER_DART_PYLON_AREA

    // Write XML
     QDomDocument document; //the xml document

    // Make the root element
    QDomElement root = document.createElement("cameraConfig");

    //Add it to the document
    document. appendChild(root);

    QDomElement machine = document.createElement("Machine");
    machine.setAttribute("Mach_ModelNumber", "i4060_modular");
    machine.setAttribute("Mach_SerialNumber", "010117001");
    machine.setAttribute("Mach_YearOfManufacture", "2017");
    machine.setAttribute("NumberOfCameras", "4");
    root.appendChild(machine);

    QDomElement camera = document.createElement("Camera");
    camera.setAttribute("CameraNumber", "0");
    camera.setAttribute("filePathName", "myNodemap.pfs");
    //camera.setAttribute("filePathName", "C:/Users/Fibrescan/Documents/BaslerFeatureFiles/daA1280-54uc_21917870.pfs");
    camera.setAttribute("Model", "daA1280-54uc");
    camera.setAttribute("SerialNumber", "21917870");
    camera.setAttribute("ManufacturerType", "FS_BASLER_DART_PYLON_AREA");
    camera.setAttribute("CameraReferenceDistance_mm", "0");
    camera.setAttribute("FrameGrabberNumber", "0");  // for Silicon Software Frame grabber
    camera.setAttribute("FrameGrabberPortNumber", "0");  // for Silicon Software Frame grabber
    machine.appendChild(camera);

    camera = document.createElement("Camera");
    camera.setAttribute("CameraNumber", "1");
    camera.setAttribute("filePathName", "myNodemap.pfs");
    //camera.setAttribute("filePathName", "C:/Users/Fibrescan/Documents/BaslerFeatureFiles/daA1280-54uc_21917871.pfs");
    camera.setAttribute("Model", "daA1280-54uc");
    camera.setAttribute("SerialNumber", "21917871");
    camera.setAttribute("ManufacturerType", "FS_BASLER_DART_PYLON_AREA");
    camera.setAttribute("CameraReferenceDistance_mm", "290");
    camera.setAttribute("FrameGrabberNumber", "0");  // for Silicon Software Frame grabber
    camera.setAttribute("FrameGrabberPortNumber", "0");  // for Silicon Software Frame grabber
    machine.appendChild(camera);


    camera = document.createElement("Camera");
    camera.setAttribute("CameraNumber", "2");
    camera.setAttribute("filePathName", "myNodemap.pfs");
    //camera.setAttribute("filePathName", "C:/Users/Fibrescan/Documents/BaslerFeatureFiles/daA1280-54uc_21917873.pfs");
    camera.setAttribute("Model", "daA1280-54uc");
    camera.setAttribute("SerialNumber", "21917873");
    camera.setAttribute("ManufacturerType", "FS_BASLER_DART_PYLON_AREA");
    camera.setAttribute("CameraReferenceDistance_mm", "290");
    camera.setAttribute("FrameGrabberNumber", "0");  // for Silicon Software Frame grabber
    camera.setAttribute("FrameGrabberPortNumber", "0");  // for Silicon Software Frame grabber
    machine.appendChild(camera);

    camera = document.createElement("Camera");
    camera.setAttribute("CameraNumber", "3");
    camera.setAttribute("filePathName", "C:/Program Files/SiliconSoftware/Runtime5.2.1/bin/MySisoMcf/YKK_BLUE_UNCUT_600DPI.mcf");
    camera.setAttribute("Model", "Mitsubishi_CIS");
    camera.setAttribute("SerialNumber", "191919");
    camera.setAttribute("ManufacturerType", "FS_SISO_CIS_RGB");
    camera.setAttribute("CameraReferenceDistance_mm", "690");
    camera.setAttribute("FrameGrabberNumber", "0");  // for Silicon Software Frame grabber
    camera.setAttribute("FrameGrabberPortNumber", "0");  // for Silicon Software Frame grabber
    machine.appendChild(camera);



    //Write to file
    QFile file ("C:/Users/Fibrescan/Documents/iScanDev1/iS_v1/ConfigFilesXML/machineCameraConfig2.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for writing";
        return false;
    }

    else
    {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "ConfigFile written";

    }
    return true; //success
}





