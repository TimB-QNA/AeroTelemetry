#ifndef modelDataSettingsManager_H
  #define modelDataSettingsManager_H

#include "pluginInterfaces.h"
#include <QtXml>

class modelDataSettingsManager
{
  public:
    modelDataSettingsManager();
    void readXML(QDomNode node);
    QStringList writeXML();
    QList<QWidget*> panelList();
    QStringList     pluginNames();
    QVariant get(QString settingName);
    void showEvent(QShowEvent *event);
    
    QList<modelDataSettingsInterface*> settings;
};

#endif

