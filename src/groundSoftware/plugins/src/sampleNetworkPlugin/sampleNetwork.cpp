#include "sampleNetwork.h"

Q_EXPORT_PLUGIN2(sampleNetwork, sampleNetwork);

sampleNetwork::sampleNetwork(QObject *parent) : QObject(parent){
  statIndicator = new QLabel("<html><font color='red'>Sample Network</font></html>");
}

QObject* sampleNetwork::asQObject(){
  return this;  
}

QString sampleNetwork::pluginName(){
  return QString("SampleNetwork");
}

QString sampleNetwork::pluginDescription(){
  return QString("Sample Network plugin - use as a basis for your own code");
}

QString sampleNetwork::xmlRootTag(){
  return QString("sample");
}

void sampleNetwork::readXML(QDomNode root){
  printf("Reading Sample Network XML\n");
  settings.readXML(root);
  emit pluginRunning();
}

QStringList sampleNetwork::writeXML(){
  printf("Writing Sample Network XML\n");
  return settings.writeXML();
}

QWidget* sampleNetwork::statusIndicator(){
  return statIndicator; 
}

void sampleNetwork::connectToPeer(){
  statIndicator->setText("<html><font color='green'>Sample Network</font></html>");
}

void sampleNetwork::disconnectFromPeer(){
  statIndicator->setText("<html><font color='red'>Sample Network</font></html>");
}

QWidget* sampleNetwork::settingsPanel(){
  return settings.guiPanel;
}

void sampleNetwork::storeSettings(){
  settings.storeGUIValues(); 
}

