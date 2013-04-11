/*
    Description: Provide Gnuplot graphs for QT4
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/


#include <QtGui>
#include "graphPlotOptions.h"
#include "telemetryDataPoint.h"

graphPlotOptions::graphPlotOptions(QList<modelData*> *model, QDialog *parent) : QDialog(parent)
{
  telemetryDataPoint tdp;
  QStringList lineTypeList;
  QGridLayout *gridLayout = new QGridLayout();

  testModel=model;
  
  setWindowTitle("Graph Options\n");
  
  lineTypeList.append("Dots");
  lineTypeList.append("Points");
  lineTypeList.append("Solid Line");
  
  modelComboLabel = new QLabel(this); gridLayout->addWidget(modelComboLabel,0,0);
  modelComboLabel->setText("Model Source");
  modelCombo = new QComboBox(this);  gridLayout->addWidget(modelCombo,0,1,1,-1);

  datasetComboLabel = new QLabel(this); gridLayout->addWidget(datasetComboLabel,1,0);
  datasetComboLabel->setText("Model Dataset");
  datasetCombo = new QComboBox(this);  gridLayout->addWidget(datasetCombo,1,1,1,-1);
  
  xComboLabel = new QLabel(this); gridLayout->addWidget(xComboLabel,2,0);
  xComboLabel->setText("X Data Source");
  xValues = new QComboBox(this);  gridLayout->addWidget(xValues,2,1,1,-1);
  xValues->addItems(tdp.fieldList);
  
  yComboLabel = new QLabel(this); gridLayout->addWidget(yComboLabel,3,0);
  yComboLabel->setText("Y Data Source");
  yValues = new QComboBox(this);  gridLayout->addWidget(yValues,3,1,1,-1);
  yValues->addItems(tdp.fieldList);

  zComboLabel = new QLabel(this); gridLayout->addWidget(zComboLabel,4,0);
  zComboLabel->setText("Z Data Source");
  zValues = new QComboBox(this);  gridLayout->addWidget(zValues,4,1,1,-1);
  zValues->addItems(tdp.fieldList);

  lineTypeLabel = new QLabel(this); gridLayout->addWidget(lineTypeLabel,5,0);
  lineTypeLabel->setText("Line Type");
  lineTypeCombo = new QComboBox(this);  gridLayout->addWidget(lineTypeCombo,5,1,1,-1);
  lineTypeCombo->addItems(lineTypeList); lineTypeCombo->setCurrentIndex(2);
  
  xMinLabel = new QLabel(this); xMinLabel->setText("Minimum X Range"); gridLayout->addWidget(xMinLabel,6,0);
  xMaxLabel = new QLabel(this); xMaxLabel->setText("Maximum X Range"); gridLayout->addWidget(xMaxLabel,7,0);
  yMinLabel = new QLabel(this); yMinLabel->setText("Minimum Y Range"); gridLayout->addWidget(yMinLabel,8,0);
  yMaxLabel = new QLabel(this); yMaxLabel->setText("Maximum Y Range"); gridLayout->addWidget(yMaxLabel,9,0);
  zMinLabel = new QLabel(this); zMinLabel->setText("Minimum Z Range"); gridLayout->addWidget(zMinLabel,10,0);
  zMaxLabel = new QLabel(this); zMaxLabel->setText("Maximum Z Range"); gridLayout->addWidget(zMaxLabel,11,0);
  
  xMinSpin = new QDoubleSpinBox(this); xMinSpin->setRange(-1e9, 1e9); gridLayout->addWidget(xMinSpin,6,1);
  xMinAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(xMinAuto,6,2);
  xMaxSpin = new QDoubleSpinBox(this); xMaxSpin->setRange(-1e9, 1e9); gridLayout->addWidget(xMaxSpin,7,1);
  xMaxAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(xMaxAuto,7,2);
  yMinSpin = new QDoubleSpinBox(this); yMinSpin->setRange(-1e9, 1e9); gridLayout->addWidget(yMinSpin,8,1);
  yMinAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(yMinAuto,8,2);
  yMaxSpin = new QDoubleSpinBox(this); yMaxSpin->setRange(-1e9, 1e9); gridLayout->addWidget(yMaxSpin,9,1);
  yMaxAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(yMaxAuto,9,2);
  zMinSpin = new QDoubleSpinBox(this); zMinSpin->setRange(-1e9, 1e9); gridLayout->addWidget(zMinSpin,10,1);
  zMinAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(zMinAuto,10,2);
  zMaxSpin = new QDoubleSpinBox(this); zMaxSpin->setRange(-1e9, 1e9); gridLayout->addWidget(zMaxSpin,11,1);
  zMaxAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(zMaxAuto,11,2);
  
  okButton = new QPushButton("Ok"); gridLayout->addWidget(okButton,12,1);
  cancelButton = new QPushButton("Cancel"); gridLayout->addWidget(cancelButton,12,2);

  clear();

  setLayout(gridLayout);

  connect(modelCombo,   SIGNAL(currentIndexChanged(int)), this, SLOT(updateDatasets(int)));
  connect(xMinAuto,     SIGNAL(toggled(bool)), xMinSpin, SLOT(setDisabled(bool)));
  connect(xMaxAuto,     SIGNAL(toggled(bool)), xMaxSpin, SLOT(setDisabled(bool)));
  connect(yMinAuto,     SIGNAL(toggled(bool)), yMinSpin, SLOT(setDisabled(bool)));
  connect(yMaxAuto,     SIGNAL(toggled(bool)), yMaxSpin, SLOT(setDisabled(bool)));
  connect(zMinAuto,     SIGNAL(toggled(bool)), zMinSpin, SLOT(setDisabled(bool)));
  connect(zMaxAuto,     SIGNAL(toggled(bool)), zMaxSpin, SLOT(setDisabled(bool)));
  connect(okButton,     SIGNAL(clicked()), this, SLOT(okClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
}

void graphPlotOptions::showEvent(QShowEvent *event){
  int i;
  // Populate combo box with current model names...
  printf("Populating model name combo-box with %i names\n", testModel->count());
  for (i=0;i<testModel->count();i++){
//    printf("ID %i - %s\n", i, testModel->at(i)->settings.get("basicSettings.modelName").toString().toAscii().data());
    modelCombo->addItem(testModel->at(i)->settings.get("basicSettings.modelName").toString());
  }
  if (modelIndex!=-1 && modelIndex<testModel->count()) modelCombo->setCurrentIndex(modelIndex);
}

void graphPlotOptions::updateDatasets(int model){
  // Currently only one dataset so just add default...
  datasetCombo->addItem("Default");
  if (dsetIndex!=-1 && dsetIndex<1) datasetCombo->setCurrentIndex(dsetIndex);
}

void graphPlotOptions::clear(){
  modelIndex=-1;
  dsetIndex=-1;
  xValIndex=0;
  yValIndex=0;
  zValIndex=0;
  lineTypeIndex=0;
  
  xRangeMin=0;
  xRangeMax=1;
  yRangeMin=0;
  yRangeMax=1;
  zRangeMin=0;
  zRangeMax=1;
  
  xMinAutoRange=true;
  xMaxAutoRange=true;
  yMinAutoRange=true;
  yMaxAutoRange=true;
  zMinAutoRange=true;
  zMaxAutoRange=true;

  modelCombo->clear();
  datasetCombo->clear();
  
  xMinAuto->setChecked(xMinAutoRange);
  xMaxAuto->setChecked(xMaxAutoRange);
  yMinAuto->setChecked(yMinAutoRange);
  yMaxAuto->setChecked(yMaxAutoRange);
  zMinAuto->setChecked(zMinAutoRange);
  zMaxAuto->setChecked(zMaxAutoRange);
  
  xMinSpin->setDisabled(xMinAutoRange);
  xMaxSpin->setDisabled(xMaxAutoRange);
  yMinSpin->setDisabled(yMinAutoRange);
  yMaxSpin->setDisabled(yMaxAutoRange);
  zMinSpin->setDisabled(zMinAutoRange);
  zMaxSpin->setDisabled(zMaxAutoRange);
}

void graphPlotOptions::okClicked(){
  modelIndex=modelCombo->currentIndex();
  dsetIndex=datasetCombo->currentIndex();
  xValIndex=xValues->currentIndex();
  yValIndex=yValues->currentIndex();
  zValIndex=zValues->currentIndex();

  xMinAutoRange=xMinAuto->isChecked();
  xMaxAutoRange=xMaxAuto->isChecked();
  yMinAutoRange=yMinAuto->isChecked();
  yMaxAutoRange=yMaxAuto->isChecked();
  zMinAutoRange=zMinAuto->isChecked();
  zMaxAutoRange=zMaxAuto->isChecked();

  xRangeMin=xMinSpin->value();
  xRangeMax=xMaxSpin->value();
  yRangeMin=yMinSpin->value();
  yRangeMax=yMaxSpin->value();
  zRangeMin=zMinSpin->value();
  zRangeMax=zMaxSpin->value();

  lineTypeIndex=lineTypeCombo->currentIndex();
  
  close();
  accept();
}

void graphPlotOptions::cancelClicked(){
  close();
  setResult(QDialog::Rejected);
}

void graphPlotOptions::print(){
  printf("   modelIndex=%i\n",modelIndex);
  printf("    dsetIndex=%i\n",dsetIndex);
  printf("    xValIndex=%i\n",xValIndex);
  printf("    yValIndex=%i\n",yValIndex);
  printf("    zValIndex=%i\n",zValIndex);
  printf("lineTypeIndex=%i\n",lineTypeIndex);

  if (xMinAutoRange) printf("xMinAutoRange=true\n");
  if (!xMinAutoRange) printf("xMinAutoRange=false\n");
  if (xMaxAutoRange) printf("xMaxAutoRange=true\n");
  if (!xMaxAutoRange) printf("xMaxAutoRange=false\n");

  if (yMinAutoRange) printf("yMinAutoRange=true\n");
  if (!yMinAutoRange) printf("yMinAutoRange=false\n");
  if (yMaxAutoRange) printf("yMaxAutoRange=true\n");
  if (!yMaxAutoRange) printf("yMaxAutoRange=false\n");

  if (zMinAutoRange) printf("zMinAutoRange=true\n");
  if (!zMinAutoRange) printf("zMinAutoRange=false\n");
  if (zMaxAutoRange) printf("zMaxAutoRange=true\n");
  if (!zMaxAutoRange) printf("zMaxAutoRange=false\n");
  
  printf("xRangeMin=%lf\n", xRangeMin);
  printf("xRangeMax=%lf\n", xRangeMax);
  printf("yRangeMin=%lf\n", yRangeMin);
  printf("yRangeMax=%lf\n", yRangeMax);
  printf("zRangeMin=%lf\n", zRangeMin);
  printf("zRangeMax=%lf\n", zRangeMax);
}

QStringList graphPlotOptions::writeXML(){
  char temp[4096];
  QStringList output;
  output.append("<options>");
  sprintf(temp,"  <modelIndex>%i</modelIndex>",modelIndex); output.append(temp);
  sprintf(temp,"  <dsetIndex>%i</dsetIndex>",dsetIndex); output.append(temp);
  sprintf(temp,"  <xValIndex>%i</xValIndex>",xValIndex); output.append(temp);
  sprintf(temp,"  <yValIndex>%i</yValIndex>",yValIndex); output.append(temp);
  sprintf(temp,"  <zValIndex>%i</zValIndex>",zValIndex); output.append(temp);
  sprintf(temp,"  <lineTypeIndex>%i</lineTypeIndex>",lineTypeIndex); output.append(temp);

  if (xMinAutoRange) { sprintf(temp,"  <xMinAutoRange>true</xMinAutoRange>");  output.append(temp); }
  if (!xMinAutoRange){ sprintf(temp,"  <xMinAutoRange>false</xMinAutoRange>"); output.append(temp); }
  if (xMaxAutoRange) { sprintf(temp,"  <xMaxAutoRange>true</xMaxAutoRange>");  output.append(temp); }
  if (!xMaxAutoRange){ sprintf(temp,"  <xMaxAutoRange>false</xMaxAutoRange>"); output.append(temp); }

  if (yMinAutoRange) { sprintf(temp,"  <yMinAutoRange>true</yMinAutoRange>");  output.append(temp); }
  if (!yMinAutoRange){ sprintf(temp,"  <yMinAutoRange>false</yMinAutoRange>"); output.append(temp); }
  if (yMaxAutoRange) { sprintf(temp,"  <yMaxAutoRange>true</yMaxAutoRange>");  output.append(temp); }
  if (!yMaxAutoRange){ sprintf(temp,"  <yMaxAutoRange>false</yMaxAutoRange>"); output.append(temp); }

  if (zMinAutoRange) { sprintf(temp,"  <zMinAutoRange>true</zMinAutoRange>");  output.append(temp); }
  if (!zMinAutoRange){ sprintf(temp,"  <zMinAutoRange>false</zMinAutoRange>"); output.append(temp); }
  if (zMaxAutoRange) { sprintf(temp,"  <zMaxAutoRange>true</zMaxAutoRange>");  output.append(temp); }
  if (!zMaxAutoRange){ sprintf(temp,"  <zMaxAutoRange>false</zMaxAutoRange>"); output.append(temp); }

  sprintf(temp,"  <xRangeMin>%lf</xRangeMin>", xRangeMin); output.append(temp);
  sprintf(temp,"  <xRangeMax>%lf</xRangeMax>", xRangeMax); output.append(temp);
  sprintf(temp,"  <yRangeMin>%lf</yRangeMin>", yRangeMin); output.append(temp);
  sprintf(temp,"  <yRangeMax>%lf</yRangeMax>", yRangeMax); output.append(temp);
  sprintf(temp,"  <zRangeMin>%lf</zRangeMin>", zRangeMin); output.append(temp);
  sprintf(temp,"  <zRangeMax>%lf</zRangeMax>", zRangeMax); output.append(temp);
  output.append("</options>");
  return output;
}

void graphPlotOptions::readXML(QDomNode root){
  QDomNode node;
  QDomElement element;
  clear();
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="modelindex")       modelIndex=element.text().toInt();
    if (element.tagName().toLower()=="dsetindex")         dsetIndex=element.text().toInt();
    if (element.tagName().toLower()=="xvalindex")         xValIndex=element.text().toInt();
    if (element.tagName().toLower()=="yvalindex")         yValIndex=element.text().toInt();
    if (element.tagName().toLower()=="zvalindex")         zValIndex=element.text().toInt();
    if (element.tagName().toLower()=="linetypeindex") lineTypeIndex=element.text().toInt();
    if (element.tagName().toLower()=="xminautorange" && element.text().toLower()=="false") xMinAutoRange=false;
    if (element.tagName().toLower()=="yminautorange" && element.text().toLower()=="false") yMinAutoRange=false;
    if (element.tagName().toLower()=="zminautorange" && element.text().toLower()=="false") zMinAutoRange=false;
    if (element.tagName().toLower()=="xrangemin") xRangeMin=element.text().toDouble();
    if (element.tagName().toLower()=="xrangemax") xRangeMax=element.text().toDouble();
    if (element.tagName().toLower()=="yrangemin") yRangeMin=element.text().toDouble();
    if (element.tagName().toLower()=="yrangemax") yRangeMax=element.text().toDouble();
    if (element.tagName().toLower()=="zrangemin") zRangeMin=element.text().toDouble();
    if (element.tagName().toLower()=="zrangemax") zRangeMax=element.text().toDouble();
    node=node.nextSibling();
  }
}

bool graphPlotOptions::graphIsValid(){
  if (modelIndex<0 || modelIndex>testModel->count()) return false;
  if (dsetIndex!=0) return false; // Modify for multiple datasets per model.
  if (xValIndex==0) return false;
  if (yValIndex==0) return false;
  return true;
}