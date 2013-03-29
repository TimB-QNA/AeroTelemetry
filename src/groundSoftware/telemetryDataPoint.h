#ifndef telemetryDataPoint_H
  #define telemetryDataPoint_H

  #include <QtXml>
  #include "odPoint.h"
  
class telemetryDataPoint
{
  public:
    
    QDateTime time;
    double frequency;
    bool positionIsGPS;
    odPoint position;
    odPoint velocity;
    odPoint attitude;

    odPoint acc;
    odPoint gyro;
    odPoint mag;
    
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
/*
    double x;
    double y;
    double z;
    
    double latitude;
    double longitude;
    double altitude;
*/
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
    void        clear();
    int         fieldIndex(QString field);
    int         unitIndex(QString unit);
    void        storeFieldData(int fieldIndex, double value, int unitType=-1);
    double      fetchFieldData(int fieldIndex);
    QString     fieldUnitString(int field);
    int         fieldUnit(int field);
    long double units(long double value, int init, int fin);
    void        print();
    bool        readXML(QDomElement root);
    QStringList writeXML();
    void        setGPSPosition(odPoint pos);
    void        setXYZPosition(odPoint pos);
};

#endif

