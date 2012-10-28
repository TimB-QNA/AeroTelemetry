// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include <QtXml>
#include "telemetryDataPoint.h"

telemetryDataPoint::telemetryDataPoint(){
  clear();
}

void telemetryDataPoint::clear(){
  time=0.;
  frequency=0.;
  accX=0.; accY=0.; accZ=0.;
  gyrX=0.; gyrY=0.; gyrZ=0.;
  magX=0.; magY=0.; magZ=0.;
  roll=0.; pitch=0.; yaw=0.;
  latitude=0.; longitude=0.; altitude=0.; track=0.; speed=0.;
  hDOP=0.; vDOP=0.; mDOP=0.;

  temperature=0.;
  voltage=0.;

  fieldList.clear();
  fieldList.append("Ignore Data");
  fieldList.append("Time");
  fieldList.append("Frequency");
  fieldList.append("Acceleration (X)");
  fieldList.append("Acceleration (Y)");
  fieldList.append("Acceleration (Z)");
  fieldList.append("Gyroscope (X)");
  fieldList.append("Gyroscope (Y)");
  fieldList.append("Gyroscope (Z)");
  fieldList.append("Magnetometer (X)");
  fieldList.append("Magnetometer (Y)");
  fieldList.append("Magnetometer (Z)");
  fieldList.append("Roll");
  fieldList.append("Pitch");
  fieldList.append("Yaw");
  fieldList.append("Latitude");
  fieldList.append("Longitude");
  fieldList.append("Altitude");
  fieldList.append("Track");
  fieldList.append("Speed");
  fieldList.append("hDOP");
  fieldList.append("vDOP");
  fieldList.append("mDOP");
  fieldList.append("Temperature");
  fieldList.append("Voltage");

  unitList.clear();
  unitList.append("unknown");
  unitList.append("non-dim");
  unitList.append("m");
  unitList.append("m/s");
  unitList.append("m/s^2");
  unitList.append("seconds");
  unitList.append("milli-seconds");
  unitList.append("deg");
  unitList.append("deg/sec");
  unitList.append("micro Tesla");
  unitList.append("Tesla");
  unitList.append("kts");
  unitList.append("Celcius");
  unitList.append("Volts");
}

int telemetryDataPoint::fieldIndex(QString field){
  int i;
  for (i=0;i<fieldList.size();i++){
    if (field==fieldList[i]) return i;
  }
  return 0; // ignore data
}

int telemetryDataPoint::unitIndex(QString unit){
  int i;
  for (i=0;i<unitList.size();i++){
    if (unit==unitList[i]) return i;
  }
  return 0; // ignore data
}

void telemetryDataPoint::storeFieldData(int field, double value, int unitType=-1){
  if (field==fieldIndex("Time"))              time=units(value,unitType,unitIndex("seconds"));
  if (field==fieldIndex("Frequency"))         frequency=value;
  if (field==fieldIndex("Acceleration (X)"))  accX=value;
  if (field==fieldIndex("Acceleration (Y)"))  accY=value;
  if (field==fieldIndex("Acceleration (Z)"))  accZ=value;
  if (field==fieldIndex("Gyroscope (X)"))     gyrX=value;
  if (field==fieldIndex("Gyroscope (Y)"))     gyrY=value;
  if (field==fieldIndex("Gyroscope (Z)"))     gyrZ=value;
  if (field==fieldIndex("Magnetometer (X)"))  magX=units(value,unitType,unitIndex("Tesla"));
  if (field==fieldIndex("Magnetometer (Y)"))  magY=units(value,unitType,unitIndex("Tesla"));
  if (field==fieldIndex("Magnetometer (Z)"))  magZ=units(value,unitType,unitIndex("Tesla"));
  if (field==fieldIndex("Roll"))              roll=value;
  if (field==fieldIndex("Pitch"))             pitch=value;
  if (field==fieldIndex("Yaw"))               yaw=value;
  if (field==fieldIndex("Latitude"))          latitude=value;
  if (field==fieldIndex("Longitude"))         longitude=value;
  if (field==fieldIndex("Altitude"))          altitude=value;
  if (field==fieldIndex("Track"))             track=value;
  if (field==fieldIndex("Speed"))             speed=units(value,unitType,unitIndex("m/s"));
  if (field==fieldIndex("hDOP"))              hDOP=units(value,unitType,unitIndex("non-dim"));
  if (field==fieldIndex("vDOP"))              vDOP=units(value,unitType,unitIndex("non-dim"));
  if (field==fieldIndex("mDOP"))              mDOP=units(value,unitType,unitIndex("non-dim"));
  if (field==fieldIndex("Temperature"))       temperature=value;
  if (field==fieldIndex("Voltage"))           voltage=value;
}

double telemetryDataPoint::fetchFieldData(int field){
  if (field==fieldIndex("Time"))              return (double)time;
  if (field==fieldIndex("Frequency"))         return frequency;
  if (field==fieldIndex("Acceleration (X)"))  return accX;
  if (field==fieldIndex("Acceleration (Y)"))  return accY;
  if (field==fieldIndex("Acceleration (Z)"))  return accZ;
  if (field==fieldIndex("Gyroscope (X)"))     return gyrX;
  if (field==fieldIndex("Gyroscope (Y)"))     return gyrY;
  if (field==fieldIndex("Gyroscope (Z)"))     return gyrZ;
  if (field==fieldIndex("Magnetometer (X)"))  return magX;
  if (field==fieldIndex("Magnetometer (Y)"))  return magY;
  if (field==fieldIndex("Magnetometer (Z)"))  return magZ;
  if (field==fieldIndex("Roll"))              return roll;
  if (field==fieldIndex("Pitch"))             return pitch;
  if (field==fieldIndex("Yaw"))               return yaw;
  if (field==fieldIndex("Latitude"))          return latitude;
  if (field==fieldIndex("Longitude"))         return longitude;
  if (field==fieldIndex("Altitude"))          return altitude;
  if (field==fieldIndex("Track"))             return track;
  if (field==fieldIndex("Speed"))             return speed;
  if (field==fieldIndex("hDOP"))              return hDOP;
  if (field==fieldIndex("vDOP"))              return vDOP;
  if (field==fieldIndex("mDOP"))              return mDOP;
  if (field==fieldIndex("Temperature"))       return temperature;
  if (field==fieldIndex("Voltage"))           return voltage;
}

double telemetryDataPoint::units(double value, int init, int fin){
  if (init==unitIndex("kts")           && fin==unitIndex("m/s"))     return value/0.514;
  if (init==unitIndex("milli-seconds") && fin==unitIndex("seconds")) return value/1000.;
  if (init==unitIndex("m")             && fin==unitIndex("non-dim")) return value/3.; // take typical commercial GPS accuracy as 3m - good enough guess in 2012
  if (init==unitIndex("micro Tesla")   && fin==unitIndex("Tesla"))   return value/1000000.;
  return value;
}

void telemetryDataPoint::print(){
  printf("Datapoint at %llf seconds\n", time);
  printf("        Acceleration %12lf\t%12lf\t%12lf\n", accX, accY, accZ);
  printf("           Gyroscope %12lf\t%12lf\t%12lf\n", gyrX, gyrY, gyrZ);
  printf("        Magnetometer %12lf\t%12lf\t%12lf\n", magX, magY, magZ);
  printf("  Position (Lat/Lon) %12lf\t%12lf\n", latitude, longitude);
  printf("            Altitude %12lf\n",altitude);
  printf("               Track %12lf\n",track);
  printf("               Speed %12lf\n",speed);
  printf("                hDOP %12lf\n",hDOP);
  printf("                vDOP %12lf\n",vDOP);
  printf("                mDOP %12lf\n",mDOP);
  printf("         Temperature %12lf\n",temperature);
  printf("             Voltage %12lf\n",voltage);
}

bool telemetryDataPoint::readXML(QDomElement root){
  QDomNode node;
  QDomElement element;
  
  if (root.tagName().toLower()!="datapoint") return false;  // If XML is not a datapoint then ignore.
  node=root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="time")        sscanf(element.text().toAscii().data(),"%llg",&time);
    if (element.tagName().toLower()=="accel")       sscanf(element.text().toAscii().data(),"%lg,%lg,%lg",&accX, &accY, &accZ);
    if (element.tagName().toLower()=="gyro")        sscanf(element.text().toAscii().data(),"%lg,%lg,%lg",&gyrX, &gyrY, &gyrZ);
    if (element.tagName().toLower()=="mag")         sscanf(element.text().toAscii().data(),"%lg,%lg,%lg",&magX, &magY, &magZ);
    if (element.tagName().toLower()=="euler")       sscanf(element.text().toAscii().data(),"%lg,%lg,%lg",&roll, &pitch, &yaw);
    if (element.tagName().toLower()=="posgps")      sscanf(element.text().toAscii().data(),"%lg,%lg,%lg,%lg,%lg",&latitude, &longitude, &altitude, &track, &speed);
    if (element.tagName().toLower()=="qualgps")     sscanf(element.text().toAscii().data(),"%lg,%lg,%lg",&hDOP,&vDOP,&mDOP);
    if (element.tagName().toLower()=="temperature") sscanf(element.text().toAscii().data(),"%lg",&temperature);
    if (element.tagName().toLower()=="voltage")        sscanf(element.text().toAscii().data(),"%lg",&voltage);
    node=node.nextSibling();
  }
  return true;
}

QStringList telemetryDataPoint::writeXML(){
  QStringList output;
  char line[4096];
  output.append("  <datapoint>");
  sprintf(line,"    <time>%llg</time>",time); output.append(line);
  sprintf(line,"    <accel>%lg,%lg,%lg</accel>",accX, accY, accZ); output.append(line);
  sprintf(line,"    <gyro>%lg,%lg,%lg</gyro>",  gyrX, gyrY, gyrZ); output.append(line);
  sprintf(line,"    <mag>%lg,%lg,%lg</mag>",    magX, magY, magZ); output.append(line);
  sprintf(line,"    <euler>%lg,%lg,%lg</euler>",roll, pitch, yaw); output.append(line);
  sprintf(line,"    <posGPS>%lg,%lg,%lg,%lg,%lg</posGPS>",latitude, longitude, altitude, track, speed); output.append(line);
  sprintf(line,"    <qualGPS>%lg,%lg,%lg</qualGPS>",hDOP, vDOP, mDOP); output.append(line);
  sprintf(line,"    <temperature>%lg</temperature>",temperature); output.append(line);
  sprintf(line,"    <voltage>%lg</voltage>",voltage); output.append(line);
  output.append("  </datapoint>");
  return output;
}