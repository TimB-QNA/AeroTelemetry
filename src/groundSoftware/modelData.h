#ifndef modelData_H
  #define modelData_H

#include "gfxDisplay.h"
#include "telemetryData.h"
#include "odPoint.h"
#include <QtXml>

class modelData
{
  public:
    modelData(gfxDisplay *d=0);
    void createGfxObject(QString filename);
    void readXML(QDomNode root);
    QStringList writeXML();

    QString name;
//    odPoint position;
    odPoint velocity;
    odPoint attitude;
    telemetryData sampleData;
    
    void addUserSphere(double x, double y, double z, double r);
    void updatePosition(double x, double y, double z);
    void updateRotation(double x, double y, double z);
    void updateGraphics(int index);
    
  private:
    int gfxModelId;
    gfxDisplay *display;
    QString geometryFile;
};

#endif

