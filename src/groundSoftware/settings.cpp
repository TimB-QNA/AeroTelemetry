// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include <QtXml>
#include <math.h>

#include "pluginInterfaces.h"
#include "settings.h"
#include "gfxDisplay.h"

extern QList<networkInterface*> network;

settings::settings(gfxDisplay *d, QDialog *parent) : QDialog(parent){
  int i;
  tabWidget = new QTabWidget();
  
  for (i=0;i<network.count();i++){
      tabWidget->addTab(network[i]->settingsPanel(), network[i]->pluginName());
  }
  
  display=d;
  QGridLayout *layout = new QGridLayout();
  layout->addWidget(tabWidget,0,0);
  setLayout(layout);
}

void settings::readXML(QDomNode root){
  int i;
  QDomNode node;
  QDomElement element;
  viewSettings vst;
  
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="scenery") sceneryFile=element.text();
    if (element.tagName().toLower()=="view"){
      if (element.attribute("ignore").toLower()!="false"){
        vst.readXML(node);
        view.append(vst);
      }
    }
    for (i=0;i<network.count();i++){
      if (element.tagName().toLower()==network[i]->xmlRootTag().toLower()) network[i]->readXML(node);
    }
    node=node.nextSibling();
  }

  if (!sceneryFile.isNull()) display->loadScenery(sceneryFile);
}

QStringList settings::writeXML(){
  int i;
  QStringList xml;
  xml.append("<settings>");
  xml.append("  <scenery>"+sceneryFile+"</scenery>");
  for (i=0;i<view.count();i++) xml.append(view[i].writeXML());
  for (i=0;i<network.count();i++) xml.append(network[i]->writeXML());
  xml.append("</settings>");
  return xml;
}

QStringList settings::viewsAvailable(){
  int i;
  QStringList vAvail;
  for (i=0;i<view.count();i++) vAvail.append(view[i].viewName);
  return vAvail;
}

void settings::storeView(){
  view[currentView].camera->GetPosition(  view[currentView].camX, view[currentView].camY, view[currentView].camZ);
  view[currentView].camera->GetFocalPoint(view[currentView].focX, view[currentView].focY, view[currentView].focZ);
  view[currentView].camera->GetViewUp(    view[currentView].upX,  view[currentView].upY,  view[currentView].upZ);
  printf("Camera Position\n");
  printf("  X = %lf\n", view[currentView].camX);
  printf("  Y = %lf\n", view[currentView].camY);
  printf("  Z = %lf\n", view[currentView].camZ);
  printf("Camera Focus\n");
  printf("  X = %lf\n", view[currentView].focX);
  printf("  Y = %lf\n", view[currentView].focY);
  printf("  Z = %lf\n", view[currentView].focZ);
  printf("Camera Up\n");
  printf("  X = %lf\n", view[currentView].upX);
  printf("  Y = %lf\n", view[currentView].upY);
  printf("  Z = %lf\n", view[currentView].upZ);
}

void settings::setView(QString vName){
  int i;
  for (i=0;i<view.count();i++){
    if (view[i].viewName==vName){
      currentView=i;
      display->setCamera(view[i]);
      break;
    }
  }
}