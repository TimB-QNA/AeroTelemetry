// Sample Gauges main program
// QT4 - Experimental stage!!

#include <math.h>
#include "modelData.h"

modelData::modelData(gfxDisplay *d){
  display=d;
}

void modelData::createGfxObject(QString filename){
  gfxModelId=display->loadModel(filename);
}

void modelData::readXML(QDomNode root){
  int i;
  QString geometryFile;
  
  QDomNode node;
  QDomElement element;
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    settings.readXML(node);
    node=node.nextSibling();
  }

  geometryFile = settings.get("basicSettings.geometryFile").toString();
  if (!geometryFile.isNull()) createGfxObject(geometryFile);
}

QStringList modelData::writeXML(){
  int i;
  QStringList xml;
  xml.append("<model>");
  settings.writeXML();
  xml.append("</model>");
  return xml;
}

void modelData::addUserSphere(double x, double y, double z, double r){
  display->model[gfxModelId]->addUserSphere(x, y, z, r);
}

void modelData::updatePosition(double x, double y, double z){
  //sampleData.insertPosition(QDateTime::currentDateTimeUtc(), odPoint(x,y,z),false);
  display->model[gfxModelId]->setPosition(x,y,z);
}

void modelData::updateRotation(double x, double y, double z){
  display->model[gfxModelId]->setRotation(x,y,z);
}

void modelData::updateGraphics(int index){
  double x, y, z;
  x=sampleData.datapoint[index].position.x;
  y=sampleData.datapoint[index].position.y;
  z=sampleData.datapoint[index].position.z;
  display->model[gfxModelId]->setPosition(x,y,z);
  
  x=sampleData.datapoint[index].roll;
  y=sampleData.datapoint[index].pitch;
  z=sampleData.datapoint[index].yaw;  
  display->model[gfxModelId]->setRotation(x,y,z);
}