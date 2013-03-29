#ifndef viewSettings_H
  #define viewSettings_H
  #include <vtkSmartPointer.h>
  #include <vtkCamera.h>
  #include <QtXml>

class viewSettings
{
  public:
    viewSettings();
    void readXML(QDomNode root);
    QStringList writeXML();

    QString viewName;
    QString refFrame;
    double camX, camY, camZ;
    double focX, focY, focZ;
    double upX,  upY,  upZ;
    vtkSmartPointer<vtkCamera> camera;
};

#endif

