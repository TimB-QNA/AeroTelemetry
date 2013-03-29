// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtXml>
#include "viewSettings.h"
#include "odPoint.h"
#include "projection.h"
extern projection planet;

viewSettings::viewSettings(){
  camera = vtkSmartPointer<vtkCamera>::New();
  refFrame="euclid";
//  refFrame="earth";
}

void viewSettings::readXML(QDomNode root){
  QDomNode node;
  QDomElement element;
  odPoint pos;
  
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="name") viewName=element.text();
    if (element.tagName().toLower()=="reference") refFrame=element.text().toLower();
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

  if (refFrame=="earth"){
    pos=planet.project(camX,camY,camZ);  camera->SetPosition(pos.x,pos.y,pos.z);
    printf("Camera Position\n");
    printf("  X = %lf\n", pos.x);
    printf("  Y = %lf\n", pos.y);
    printf("  Z = %lf\n", pos.z);
    pos=planet.project(focX,focY,focZ);  camera->SetFocalPoint(pos.x,pos.y,pos.z);
    printf("Camera Focus\n");
    printf("  X = %lf\n", pos.x);
    printf("  Y = %lf\n", pos.y);
    printf("  Z = %lf\n", pos.z);
    pos=planet.project(upX,upY,upZ);     camera->SetViewUp(pos.x,pos.y,pos.z);
    printf("Camera Up\n");
    printf("  X = %lf\n", pos.x);
    printf("  Y = %lf\n", pos.y);
    printf("  Z = %lf\n", pos.z);
  }else{
    camera->SetPosition(camX,camY,camZ);
    camera->SetFocalPoint(focX,focY,focZ);
    camera->SetViewUp(upX,upY,upZ);
  }
}

QStringList viewSettings::writeXML(){
  char line[4096];
  QStringList xml;
  xml.append("  <view>");
  xml.append("    <name>"+viewName+"</name>");
  xml.append("    <reference>"+refFrame+"</reference>");
  sprintf(line,"    <camera   x='%lg' y='%lg' z='%lg'/>", camX, camY, camZ); xml.append(line);
  sprintf(line,"    <focus    x='%lg' y='%lg' z='%lg'/>", focX, focY, focZ); xml.append(line);
  sprintf(line,"    <upVector x='%lg' y='%lg' z='%lg'/>", upX,  upY,  upZ);  xml.append(line);
  xml.append("  </view>");
  return xml;
}