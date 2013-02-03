/*
    Description: Provide Gnuplot graphs for QT4
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/


#include <QtGui>
#include "mdiPlotOptions.h"
#include "telemetryDataPoint.h"

mdiPlotOptions::mdiPlotOptions(QDialog *parent) : QDialog(parent)
{
  telemetryDataPoint tdp;
  QStringList lineTypeList;
  QGridLayout *gridLayout = new QGridLayout();

  setWindowTitle("Graph Options\n");
  
  lineTypeList.append("Dots");
  lineTypeList.append("Points");
  lineTypeList.append("Solid Line");
  
  xComboLabel = new QLabel(this); gridLayout->addWidget(xComboLabel,0,0);
  xComboLabel->setText("X Data Source");
  xValues = new QComboBox(this);  gridLayout->addWidget(xValues,0,1,1,-1);
  xValues->addItems(tdp.fieldList);
  
  yComboLabel = new QLabel(this); gridLayout->addWidget(yComboLabel,1,0);
  yComboLabel->setText("Y Data Source");
  yValues = new QComboBox(this);  gridLayout->addWidget(yValues,1,1,1,-1);
  yValues->addItems(tdp.fieldList);

  zComboLabel = new QLabel(this); gridLayout->addWidget(zComboLabel,2,0);
  zComboLabel->setText("Z Data Source");
  zValues = new QComboBox(this);  gridLayout->addWidget(zValues,2,1,1,-1);
  zValues->addItems(tdp.fieldList);

  lineTypeLabel = new QLabel(this); gridLayout->addWidget(lineTypeLabel,3,0);
  lineTypeLabel->setText("Line Type");
  lineTypeCombo = new QComboBox(this);  gridLayout->addWidget(lineTypeCombo,3,1,1,-1);
  lineTypeCombo->addItems(lineTypeList); lineTypeCombo->setCurrentIndex(2);
  
  xMinLabel = new QLabel(this); xMinLabel->setText("Minimum X Range"); gridLayout->addWidget(xMinLabel,4,0);
  xMaxLabel = new QLabel(this); xMaxLabel->setText("Maximum X Range"); gridLayout->addWidget(xMaxLabel,5,0);
  yMinLabel = new QLabel(this); yMinLabel->setText("Minimum Y Range"); gridLayout->addWidget(yMinLabel,6,0);
  yMaxLabel = new QLabel(this); yMaxLabel->setText("Maximum Y Range"); gridLayout->addWidget(yMaxLabel,7,0);
  zMinLabel = new QLabel(this); zMinLabel->setText("Minimum Z Range"); gridLayout->addWidget(zMinLabel,8,0);
  zMaxLabel = new QLabel(this); zMaxLabel->setText("Maximum Z Range"); gridLayout->addWidget(zMaxLabel,9,0);
  
  xMinSpin = new QDoubleSpinBox(this); xMinSpin->setRange(-1e9, 1e9); gridLayout->addWidget(xMinSpin,4,1);
  xMinAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(xMinAuto,4,2);
  xMaxSpin = new QDoubleSpinBox(this); xMaxSpin->setRange(-1e9, 1e9); gridLayout->addWidget(xMaxSpin,5,1);
  xMaxAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(xMaxAuto,5,2);
  yMinSpin = new QDoubleSpinBox(this); yMinSpin->setRange(-1e9, 1e9); gridLayout->addWidget(yMinSpin,6,1);
  yMinAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(yMinAuto,6,2);
  yMaxSpin = new QDoubleSpinBox(this); yMaxSpin->setRange(-1e9, 1e9); gridLayout->addWidget(yMaxSpin,7,1);
  yMaxAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(yMaxAuto,7,2);
  zMinSpin = new QDoubleSpinBox(this); zMinSpin->setRange(-1e9, 1e9); gridLayout->addWidget(zMinSpin,8,1);
  zMinAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(zMinAuto,8,2);
  zMaxSpin = new QDoubleSpinBox(this); zMaxSpin->setRange(-1e9, 1e9); gridLayout->addWidget(zMaxSpin,9,1);
  zMaxAuto = new QCheckBox("Auto-range",this); gridLayout->addWidget(zMaxAuto,9,2);
  
  okButton = new QPushButton("Ok"); gridLayout->addWidget(okButton,10,1);
  cancelButton = new QPushButton("Cancel"); gridLayout->addWidget(cancelButton,10,2);

  clear();

  setLayout(gridLayout);

  connect(xMinAuto, SIGNAL(toggled(bool)), xMinSpin, SLOT(setDisabled(bool)));
  connect(xMaxAuto, SIGNAL(toggled(bool)), xMaxSpin, SLOT(setDisabled(bool)));
  connect(yMinAuto, SIGNAL(toggled(bool)), yMinSpin, SLOT(setDisabled(bool)));
  connect(yMaxAuto, SIGNAL(toggled(bool)), yMaxSpin, SLOT(setDisabled(bool)));
  connect(zMinAuto, SIGNAL(toggled(bool)), zMinSpin, SLOT(setDisabled(bool)));
  connect(zMaxAuto, SIGNAL(toggled(bool)), zMaxSpin, SLOT(setDisabled(bool)));
  connect(okButton,     SIGNAL(clicked()), this, SLOT(okClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
}

void mdiPlotOptions::clear(){
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

void mdiPlotOptions::okClicked(){
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

void mdiPlotOptions::cancelClicked(){
  close();
  setResult(QDialog::Rejected);
}

void mdiPlotOptions::print(){
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