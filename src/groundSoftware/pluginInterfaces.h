#ifndef PLUGININTERFACES_H
#define PLUGININTERFACES_H

#include <QtGui>
#include <QtPlugin>
#include <QtXml>
//#include "gfxObject.h"

class gfxObject; // Fwd Declaration

class networkInterface
{
  public:  
    virtual QObject* asQObject() = 0;
    virtual void readXML(QDomNode root)=0;
    virtual QStringList writeXML()=0;
    virtual QString xmlRootTag()=0;
    virtual QString pluginName()=0;
    virtual QString pluginDescription()=0;

    // GUI elements
    virtual QWidget* statusIndicator()=0;
    virtual QWidget* settingsPanel()=0;
    virtual void storeSettings()=0;
     
  public slots:
    virtual void connectToPeer()=0;
    virtual void disconnectFromPeer()=0;
};

Q_DECLARE_INTERFACE(networkInterface, "AeroTelemetry.networkInterface/1.0")

class modelDataSettingsInterface
{
  public:
    virtual QObject* asQObject() = 0;
    virtual void readXML(QDomNode root)=0;
    virtual QStringList writeXML()=0;
    virtual QString xmlRootTag()=0;
    virtual QString pluginName()=0;
    virtual QString pluginDescription()=0;

    // GUI elements
    virtual QWidget* settingsPanel()=0;
    virtual void storeSettings()=0;
    virtual void showEvent(QShowEvent *event)=0;

    // Settings search
    virtual QVariant get(QString settingName)=0;
};

Q_DECLARE_INTERFACE(modelDataSettingsInterface, "AeroTelemetry.modelDataSettingsInterface/1.0")

class cadFormatInterface
{
  public:
    virtual QObject* asQObject() = 0;
    virtual QString pluginName()=0;
    virtual QString pluginDescription()=0;

    virtual bool loadCAD(QString filename)=0;
    virtual void setParentObject(gfxObject *obj)=0;
};

Q_DECLARE_INTERFACE(cadFormatInterface, "AeroTelemetry.cadFormatInterface/1.0")
#endif