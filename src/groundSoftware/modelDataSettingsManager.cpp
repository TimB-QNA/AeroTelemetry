// Sample Gauges main program
// QT4 - Experimental stage!!

#include <math.h>
#include "modelData.h"

modelDataSettingsManager::modelDataSettingsManager(){
  int i;
  modelDataSettingsInterface *settingsPlugin;
  printf("Loading settings plugins:\n");
  // Load plugins...
  QDir pluginDir("plugins");
  QStringList pluginFiles;
  pluginDir.setNameFilters(QStringList(QString("*.so")));
  pluginFiles=pluginDir.entryList();
  for (i=0;i<pluginFiles.count();i++){
//    printf("Trying to load - %s\n",pluginFiles[i].toAscii().data());
    QPluginLoader loader(pluginDir.path()+"/"+pluginFiles[i]);
    settingsPlugin = qobject_cast<modelDataSettingsInterface *> (loader.instance());
    if (settingsPlugin){
      printf("%s\t-\t%s\n", settingsPlugin->pluginName().toAscii().data(), settingsPlugin->pluginDescription().toAscii().data());
      settings.append(settingsPlugin);
    }
  }
}

void modelDataSettingsManager::readXML(QDomNode root){
  int i;
  QDomNode node;
  QDomElement element, rootElement;

  rootElement=root.toElement();
  if (rootElement.tagName().toLower()=="settings"){
    node = root.firstChild();
    while (!node.isNull()){
      element=node.toElement();
      for (i=0;i<settings.count();i++){
        if (element.tagName().toLower()==settings[i]->xmlRootTag().toLower()) settings[i]->readXML(node);
      }
      node=node.nextSibling();
    }
  }
}

QStringList modelDataSettingsManager::writeXML(){
  int i;
  QStringList xml;
  xml.append("<settings>");
  for (i=0;i<settings.count();i++) xml.append(settings[i]->writeXML());
  xml.append("</settings>");
  return xml;
}

QList<QWidget*> modelDataSettingsManager::panelList(){
  int i;
  QList<QWidget*> pList;
  for (i=0;i<settings.count();i++) pList.append(settings[i]->settingsPanel());
  return pList;
}

QStringList modelDataSettingsManager::pluginNames(){
  int i;
  QStringList pList;
  for (i=0;i<settings.count();i++) pList.append(settings[i]->pluginName());
  return pList;
}

QVariant modelDataSettingsManager::get(QString settingName){
  int i;
  QVariant result;
  
  for (i=0;i<settings.count();i++){
    result=settings[i]->get(settingName);
    if (!result.isNull()) return result;
  }
  
  return result;
}

void modelDataSettingsManager::showEvent(QShowEvent *event){
  int i;
  for (i=0;i<settings.count();i++) settings[i]->showEvent(event);
}