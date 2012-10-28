#ifndef telemetryData_H
  #define telemetryData_H

  #include <QtXml>
  #include "telemetryDataPoint.h"
  
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
  
//  private:
    QList<telemetryDataPoint> datapoint;
};

#endif

