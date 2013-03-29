#ifndef telemetryData_H
  #define telemetryData_H

  #include <QtXml>
  #include "telemetryDataPoint.h"
  #include "projection.h"
  
class telemetryData
{
  public: 
    telemetryData();
    int size();

    void importFromFile(QString fileName, QRegExp separator, QList<int> fieldList, QList<int> unitList, int header);
    void readXML(QString fileName);
    void readXML(QDomElement root);
    void writeXML(QString fileName);
    QStringList writeXML();
    double   mean(double xMin, double xMax, bool wholeSignal, int xIndex, int yIndex);
    double    rms(double xMin, double xMax, bool wholeSignal, int xIndex, int yIndex);
    double rmsDev(double xMin, double xMax, bool wholeSignal, int xIndex, int yIndex);
    double avgDev(double xMin, double xMax, bool wholeSignal, int xIndex, int yIndex);

    void insertPosition(QDateTime time, odPoint pos, bool checkTime=false);
    
//  private:
    projection::projectionType proMethod; // 0=none 1=spherical
    QList<telemetryDataPoint> datapoint;
    telemetryDataPoint meanVals;
    telemetryDataPoint rmsVals;
};

#endif

