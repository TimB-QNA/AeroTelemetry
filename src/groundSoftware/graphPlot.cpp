/*
    Description: Provide Gnuplot graphs for QT4
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/


#include <QtGui>
#include "graphPlot.h"

graphPlot::graphPlot(QList<modelData*> *model, QWidget *parent) : qt4gnuplot(parent)
{
  testModel=model;
  
  QGridLayout *gridLayout = new QGridLayout();
  
  setContextMenuPolicy(Qt::ActionsContextMenu);
  
  options = new graphPlotOptions(testModel);
  showOptionsAction = new QAction("Options",this);
  addAction(showOptionsAction);

//  stats = new statisticsDisplay(options);
//  showStatsAction = new QAction("Statistics",this);
//  addAction(showStatsAction);
  
  connect(showOptionsAction, SIGNAL(activated()), options, SLOT(show()));
  connect(options,           SIGNAL(accepted()),  this,    SLOT(scriptGraph()));
//  connect(showStatsAction,   SIGNAL(activated()), stats,   SLOT(show()));
}

void graphPlot::showEvent(QShowEvent *event){
  scriptGraph();
}

void graphPlot::scriptGraph(){
  QString lineType;
  telemetryDataPoint tdp;
  int i;
  char line [4096];
  
  if (!options->graphIsValid()){
    stdGraph();
    return;
  }
  
  script.clear();
  script.append("set grid");
  script.append("set xlabel \""+tdp.fieldList[options->xValIndex]+"\"");
  script.append("set ylabel \""+tdp.fieldList[options->yValIndex]+"\"");

  if (options->xMinAutoRange && !options->xMaxAutoRange){
    sprintf(line,"set xrange [*:%lg]",options->xRangeMax);
    script.append(line);
  }
  if (!options->xMinAutoRange && options->xMaxAutoRange){
    sprintf(line,"set xrange [%lg:*]",options->xRangeMin);
    script.append(line);
  }
  if (!options->xMinAutoRange && !options->xMaxAutoRange){
    sprintf(line,"set xrange [%lg:%lg]",options->xRangeMin,options->xRangeMax);
    script.append(line);
  }

  if (options->yMinAutoRange && !options->yMaxAutoRange){
    sprintf(line,"set yrange [*:%lg]",options->yRangeMax);
    script.append(line);
  }
  if (!options->yMinAutoRange && options->yMaxAutoRange){
    sprintf(line,"set yrange [%lg:*]",options->yRangeMin);
    script.append(line);
  }
  if (!options->yMinAutoRange && !options->yMaxAutoRange){
    sprintf(line,"set xrange [%lg:%lg]",options->yRangeMin,options->yRangeMax);
    script.append(line);
  }

  if (options->zMinAutoRange && !options->zMaxAutoRange){
    sprintf(line,"set zrange [*:%lg]",options->zRangeMax);
    script.append(line);
  }
  if (!options->zMinAutoRange && options->zMaxAutoRange){
    sprintf(line,"set zrange [%lg:*]",options->zRangeMin);
    script.append(line);
  }
  if (!options->zMinAutoRange && !options->zMaxAutoRange){
    sprintf(line,"set zrange [%lg:%lg]",options->zRangeMin,options->zRangeMax);
    script.append(line);
  }
   
  if (options->lineTypeIndex==0) lineType="dots";
  if (options->lineTypeIndex==1) lineType="points";
  if (options->lineTypeIndex==2) lineType="lines";
  
  if (options->zValIndex==0){
    script.append(QString("plot '-' with ")+lineType);
  }else{
    script.append(QString("splot '-' with ")+lineType);
  }
//  printf("Data Points = %i\n",dataset.size());
  for (i=0;i<dataset.size();i++){
    sprintf(line,"%lg %lg %lg", dataset.datapoint[i].fetchFieldData(options->xValIndex), dataset.datapoint[i].fetchFieldData(options->yValIndex), dataset.datapoint[i].fetchFieldData(options->zValIndex));
    script.append(line);
  }
  script.append("e");
//  for (i=0;i<script.size();i++) printf("%s\n",script[i].toAscii().data());
  plotgraph();
}

void graphPlot::stdGraph(){
  int i;
  //Plot inter-locking Tori - from GNUPlot Examples
  script.clear();

  script.append("set parametric");
  script.append("set urange [-pi:pi]");
  script.append("set vrange [-pi:pi]");
  script.append("set isosamples 50,20");

  script.append("unset key");
  script.append("unset xtics");
  script.append("unset ytics");
  script.append("unset ztics");
  script.append("set border 0");
  script.append("set view 60, 30, 1.5, 0.9");
  script.append("unset colorbox");
  script.append("set title \"Tori\"");

  script.append("set colorbox vertical user origin 0.9, 0.15 size 0.02, 0.50");
  script.append("set format cb '%.1f'");

  script.append("set pm3d depthorder");
  script.append("splot cos(u)+.5*cos(u)*cos(v),sin(u)+.5*sin(u)*cos(v),.5*sin(v) with pm3d, 1+cos(u)+.5*cos(u)*cos(v),.5*sin(v),sin(u)+.5*sin(u)*cos(v) with pm3d");

//  for (i=0;i<script.size();i++) printf("%s\n",script[i].toAscii().data());
  plotgraph();
}

QStringList graphPlot::writeXML(){
  QStringList output;

  output.append("<graph>");
  output.append(options->writeXML());
  output.append("</graph>");
  return output;
}

void graphPlot::readXML(QDomNode root){
  QDomNode node;
  QDomElement element;
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="options") options->readXML(node);
    node=node.nextSibling();
  }
}