/*
    Description: Provide Gnuplot graphs for QT4
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/


#include <QtGui>
#include "statisticsDisplay.h"
#include "telemetryDataPoint.h"
#include "mdiPlot.h"

extern telemetryData dataset;

statisticsDisplay::statisticsDisplay(mdiPlotOptions *opt, QDialog *parent) : QDialog(parent)
{
  telemetryDataPoint tdp;
  QGridLayout *gridLayout = new QGridLayout();

  options=opt;
  
  setWindowTitle("Statistics\n");
  displayLabel = new QTextEdit(this); gridLayout->addWidget(displayLabel,0,0,1,4);
  wholeSignalCheck = new QCheckBox("Use whole signal",this); gridLayout->addWidget(wholeSignalCheck,1,0);
  recalcButton = new QPushButton("Re-calculate"); gridLayout->addWidget(recalcButton,2,0);
  closeButton  = new QPushButton("Close"); gridLayout->addWidget(closeButton,2,3);
  connect(recalcButton, SIGNAL(clicked()), this, SLOT(recalculateStats()));
  connect(closeButton,  SIGNAL(clicked()), this, SLOT(close()));
  setLayout(gridLayout);
  clear();
}

void statisticsDisplay::clear(){
  yValMean=0.;
  yValRms=0.;
  yValRmsDev=0.;
  yValAvgDev=0.;
  zValMean=0.;
  zValRms=0.;
  zValRmsDev=0.;
  zValAvgDev=0.;
  writeStatsBox();
}

void statisticsDisplay::recalculateStats(){
  if (options->yValIndex!=0){
    yValMean  =dataset.mean(options->xRangeMin, options->xRangeMax, wholeSignalCheck->isChecked(), options->xValIndex, options->yValIndex);
    yValRms   =dataset.rms(options->xRangeMin, options->xRangeMax, wholeSignalCheck->isChecked(), options->xValIndex, options->yValIndex);
    yValRmsDev=dataset.rmsDev(options->xRangeMin, options->xRangeMax, wholeSignalCheck->isChecked(), options->xValIndex, options->yValIndex);
    yValAvgDev=dataset.avgDev(options->xRangeMin, options->xRangeMax, wholeSignalCheck->isChecked(), options->xValIndex, options->yValIndex);
  }

  if (options->yValIndex!=0){
    zValMean  =dataset.mean(options->xRangeMin, options->xRangeMax, wholeSignalCheck->isChecked(), options->xValIndex, options->zValIndex);
    zValRms   =dataset.rms(options->xRangeMin, options->xRangeMax, wholeSignalCheck->isChecked(), options->xValIndex, options->zValIndex);
    zValRmsDev=dataset.rmsDev(options->xRangeMin, options->xRangeMax, wholeSignalCheck->isChecked(), options->xValIndex, options->zValIndex);
    zValAvgDev=dataset.avgDev(options->xRangeMin, options->xRangeMax, wholeSignalCheck->isChecked(), options->xValIndex, options->zValIndex);
  }
  writeStatsBox();
}

void statisticsDisplay::writeStatsBox(){
  telemetryDataPoint tdp;
  QString html;
  char line[4096];
//  options->print();
  html="<center><h2>Signal Statistics</h2></center><br>";
  html+="<table border='1' width='80%'>";
  html+="<tr><th>General Stats</th></tr>";

  html+="<tr><td></td>";
  if (options->yValIndex!=0) html+="<th colspan='2'>"+tdp.fieldList[options->yValIndex]+"</td></tr>";
  if (options->zValIndex!=0) html+="<th colspan='2'>"+tdp.fieldList[options->zValIndex]+"</td></tr>";

  html+="<tr><th>Mean</th>";
  if (options->yValIndex!=0){ sprintf(line,"<td>%lg</td>",yValMean); html+=QString(line)+"<td>"+tdp.fieldUnitString(options->yValIndex)+"</td>"; }
  if (options->zValIndex!=0){ sprintf(line,"<td>%lg</td>",zValMean); html+=QString(line)+"<td>"+tdp.fieldUnitString(options->zValIndex)+"</td>"; }
  html+="</tr>";

  html+="<tr><th>RMS</th>";
  if (options->yValIndex!=0){ sprintf(line,"<td>%lg</td>",yValRms); html+=QString(line)+"<td>"+tdp.fieldUnitString(options->yValIndex)+"</td>"; }
  if (options->zValIndex!=0){ sprintf(line,"<td>%lg</td>",zValRms); html+=QString(line)+"<td>"+tdp.fieldUnitString(options->zValIndex)+"</td>"; }
  html+="</tr>";

  html+="<tr></tr>";
  html+="<tr><th>Deviation Stats</th></tr>";

  html+="<tr><th>RMS Deviation</th>";
  if (options->yValIndex!=0){ sprintf(line,"<td>%lg</td>",yValRmsDev); html+=QString(line)+"<td>"+tdp.fieldUnitString(options->yValIndex)+"</td>"; }
  if (options->zValIndex!=0){ sprintf(line,"<td>%lg</td>",zValRmsDev); html+=QString(line)+"<td>"+tdp.fieldUnitString(options->zValIndex)+"</td>"; }
  html+="</tr>";

  html+="<tr><th>Average Deviation</th>";
  if (options->yValIndex!=0){ sprintf(line,"<td>%lg</td>",yValAvgDev); html+=QString(line)+"<td>"+tdp.fieldUnitString(options->yValIndex)+"</td>"; }
  if (options->zValIndex!=0){ sprintf(line,"<td>%lg</td>",zValAvgDev); html+=QString(line)+"<td>"+tdp.fieldUnitString(options->zValIndex)+"</td>"; }
  html+="</tr>";
  html+="</table>";
  
  displayLabel->setHtml(html);
}
