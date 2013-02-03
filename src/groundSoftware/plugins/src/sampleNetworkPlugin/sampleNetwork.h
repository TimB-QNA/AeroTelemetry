#ifndef sampleNetwork_H
  #define sampleNetwork_H

#include <QObject>
#include <QtPlugin>
#include <QtNetwork>
#include "../../../pluginInterfaces.h"
#include "sampleSettings.h"

class sampleNetwork : public QObject, public networkInterface
{
  Q_OBJECT
  Q_INTERFACES(networkInterface)
  
  public:
    sampleNetwork(QObject *parent=0);
    QObject* asQObject();
    QString pluginName();
    QString pluginDescription();
    QString xmlRootTag();
    void readXML(QDomNode root);
    QStringList writeXML();
    QWidget* statusIndicator();
    QWidget* settingsPanel();
    void storeSettings();

  public slots:
     virtual void connectToPeer();
     virtual void disconnectFromPeer();
     
  signals:
    void pluginRunning();
    
  private:
    sampleSettings settings;
    QLabel *statIndicator;
};
#endif