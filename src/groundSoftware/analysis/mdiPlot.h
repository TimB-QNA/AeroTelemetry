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
#include "mdiPlotOptions.h"
#include <qt4gnuplot.h>

class QDESIGNER_WIDGET_EXPORT mdiPlot : public qt4gnuplot
{
   Q_OBJECT
   
  public:
    mdiPlot(QWidget *parent=0);
    
  private:
    mdiPlotOptions *options;
    QAction *showOptionsAction;
    void stdGraph();
    
  private slots:
    void scriptGraph();
};

#endif

