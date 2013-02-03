/*
    Description: Provide Gnuplot graphs for QT4 (Class Header)
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/

#ifndef statisticsDisplay_H
  #define statisticsDisplay_H

#include <QtGui>
#include <QtDesigner/QDesignerExportWidget>
#include "mdiPlotOptions.h"

class QDESIGNER_WIDGET_EXPORT statisticsDisplay : public QDialog
{
   Q_OBJECT
   
  public:
    statisticsDisplay(mdiPlotOptions *opt, QDialog *parent=0);
    mdiPlotOptions *options;
    
  private:
    // Amplitude figures
    double yValMean=0.;
    double yValRms=0.;
    double zValMean=0.;
    double zValRms=0.;
    
    // Deviation figures
    double yValRmsDev=0.;
    double yValAvgDev=0.;
    double zValRmsDev=0.;
    double zValAvgDev=0.;
    
    QTextEdit   *displayLabel;
    QCheckBox   *wholeSignalCheck;
    QPushButton *recalcButton;
    QPushButton *closeButton;
    void writeStatsBox();
    void clear();
    
  private slots:
    void recalculateStats();
};

#endif

