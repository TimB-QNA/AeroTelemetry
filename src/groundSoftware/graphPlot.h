/*
    Description: Provide Gnuplot graphs for QT4 (Class Header)
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/

#ifndef mdiPlot_H
  #define mdiPlot_H

#include <QtGui>
#include <QtDesigner/QDesignerExportWidget>
#include "telemetryData.h"
#include "graphPlotOptions.h"
//#include "statisticsDisplay.h"
#include "modelData.h"
#include <qt4gnuplot.h>

class graphPlot : public qt4gnuplot
{
   Q_OBJECT
   
  public:
    graphPlot(QList<modelData*> *model, QWidget *parent=0);
    void readXML(QDomNode root);
    QStringList writeXML();
    
  private:
    QList<modelData*> *testModel;
    telemetryData dataset;
    graphPlotOptions *options;
//    statisticsDisplay *stats;
    QAction *showOptionsAction;
    QAction *showStatsAction;
    void stdGraph();
    
  private slots:
    void scriptGraph();
    void showEvent(QShowEvent *event);
};

#endif

