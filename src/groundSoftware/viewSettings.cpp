// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtXml>
#include "viewSettings.h"

viewSettings::viewSettings(){
  camera = vtkSmartPointer<vtkCamera>::New();
}

void viewSettings::readXML(QDomNode root){
  QDomNode node;
  QDomElement element;
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="name") viewName=element.text();
//    if (element.tagName().toLower()=="reference") refFrame=element.text();
    if (element.tagName().toLower()=="camera"){
      camX=element.attribute("x").toDouble();
      camY=element.attribute("y").toDouble();
      camZ=element.attribute("z").toDouble();
    }
    if (element.tagName().toLower()=="focus"){
      focX=element.attribute("x").toDouble();
      focY=element.attribute("y").toDouble();
      focZ=element.attribute("z").toDouble();
    }
    if (element.tagName().toLower()=="upvector"){
      upX=element.attribute("x").toDouble();
      upY=element.attribute("y").toDouble();
      upZ=element.attribute("z").toDouble();
    }
    node=node.nextSibling();
  }

  camera->SetPosition(camX,camY,camZ);
  camera->SetFocalPoint(focX,focY,focZ);
  camera->SetViewUp(upX,upY,upZ);
}

QStringList viewSettings::writeXML(){
  char line[4096];
  QStringList xml;
  xml.append("  <view>");
  xml.append("    <name>"+viewName+"</name>");
//  xml.append("    <reference>World</reference>");
  sprintf(line,"    <camera   x='%lg' y='%lg' z='%lg'/>", camX, camY, camZ); xml.append(line);
  sprintf(line,"    <focus    x='%lg' y='%lg' z='%lg'/>", focX, focY, focZ); xml.append(line);
  sprintf(line,"    <upVector x='%lg' y='%lg' z='%lg'/>", upX,  upY,  upZ);  xml.append(line);
  xml.append("  </view>");
  return xml;
}