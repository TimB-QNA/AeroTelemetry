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
  QDomNode node;
  QDomElement element;
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="name") name=element.text();
    if (element.tagName().toLower()=="geometry") geometryFile=element.text();
    node=node.nextSibling();
  }

  if (!geometryFile.isNull()) createGfxObject(geometryFile);
}

QStringList modelData::writeXML(){
  QStringList xml;
  xml.append("<model>");
  xml.append("  <name>"+name+"</name>");
  xml.append("  <geometry>"+geometryFile+"</geometry>");
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