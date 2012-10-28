// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include <QtXml>
#include "telemetryData.h"

telemetryData::telemetryData(){

}

int telemetryData::size(){
  return datapoint.size();
}

void telemetryData::importFromFile(QString fileName, QRegExp separator, QList<int> fieldList, QList<int> unitList, int header){
  int i, j;
  telemetryDataPoint tdp;
  QFile inputFile(fileName);
  QStringList dataValues;
  
  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) return;

  i=0;
  while (!inputFile.atEnd()){
    dataValues=QString(inputFile.readLine()).split(separator, QString::KeepEmptyParts);
    dataValues.pop_back();
    if (i>header){
      tdp=telemetryDataPoint();
      for (j=0;j<dataValues.size();j++){
        tdp.storeFieldData(fieldList[j], dataValues[j].toDouble(), unitList[j]);
      }
      datapoint.append(tdp);
    }  
    i++;
  }
  inputFile.close();
  datapoint.pop_back();
}

void telemetryData::readXML(QString fileName){
  QDomElement root;
  QDomNode node, node2;
  QDomElement element, element2;
  QFile file(fileName);
  
  if (!file.open( QIODevice::ReadOnly )){ printf("Could not open data file\n"); return; }

  QDomDocument doc( "dataset" );
  if (!doc.setContent( &file )){ printf("Failed to set content\n"); file.close(); return; }
  file.close();
  root=doc.documentElement();
  if (root.tagName().toLower() != "telemetry"){ printf("This is not a telemetry XML file\n"); return; }
  readXML(root);
}

void telemetryData::readXML(QDomElement root){
  QDomNode node;
  QDomElement element;
  telemetryDataPoint tdp;
  
  node=root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    tdp.clear();
    if (tdp.readXML(element)) datapoint.append(tdp);
    node=node.nextSibling();
  }
  return;
}

void telemetryData::writeXML(QString fileName){
  QFile outFile(fileName);
  if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;
  outFile.write(writeXML().join("\n").toAscii());
  outFile.close();
}

QStringList telemetryData::writeXML(){
  int i;
  QStringList output;
  
  output.append("<telemetry>");
  for (i=0;i<datapoint.size();i++) output.append(datapoint[i].writeXML());
  output.append("</telemetry>");
  return output;
}