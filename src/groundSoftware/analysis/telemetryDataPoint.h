#ifndef telemetryDataPoint_H
  #define telemetryDataPoint_H

  #include <QtXml>
  
class telemetryDataPoint
{
  public:
    
    long double time;
    double frequency;
    double accX;
    double accY;
    double accZ;

    double gyrX;
    double gyrY;
    double gyrZ;

    double magX;
    double magY;
    double magZ;

    double roll;
    double pitch;
    double yaw;
    
    double latitude;
    double longitude;
    double altitude;
    double track;
    double speed;
    double hDOP;
    double vDOP;
    double mDOP;

    double temperature;
    double voltage;
    
    QStringList fieldList;
    QStringList unitList;
    
           telemetryDataPoint();
    void   clear();
    int    fieldIndex(QString field);
    int    unitIndex(QString unit);
    void   storeFieldData(int fieldIndex, double value, int unitType);
    double fetchFieldData(int fieldIndex);
    double units(double value, int init, int fin);
    void   print();
    bool   readXML(QDomElement root);
    QStringList writeXML();
};

#endif

