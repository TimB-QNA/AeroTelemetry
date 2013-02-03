#ifndef PLUGININTERFACES_H
#define PLUGININTERFACES_H

#include <QtPlugin>
#include <QtXml>

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

Q_DECLARE_INTERFACE(networkInterface, "ModelDisplay.networkInterface/1.0")

#endif