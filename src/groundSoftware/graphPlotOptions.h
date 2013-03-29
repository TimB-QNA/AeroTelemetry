/*
    Description: Provide Gnuplot graphs for QT4 (Class Header)
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/

#ifndef graphPlotOptions_H
  #define graphPlotOptions_H

#include <QtGui>
#include <QtDesigner/QDesignerExportWidget>
#include "modelData.h"

class graphPlotOptions : public QDialog
{
   Q_OBJECT
   
  public:
    graphPlotOptions(QList<modelData*> *model, QDialog *parent=0);
    QList<modelData*> *testModel;
    void print();
    QStringList writeXML();
    void readXML(QDomNode root);
    bool graphIsValid();
    
    int modelIndex;
    int dsetIndex;
    int xValIndex;
    int yValIndex;
    int zValIndex;
    int lineTypeIndex;
    
    bool xMinAutoRange;
    bool xMaxAutoRange;
    bool yMinAutoRange;
    bool yMaxAutoRange;
    bool zMinAutoRange;
    bool zMaxAutoRange;

    double xRangeMin;
    double xRangeMax;
    double yRangeMin;
    double yRangeMax;
    double zRangeMin;
    double zRangeMax;
    
  private:
    QComboBox *modelCombo;
    QComboBox *datasetCombo;
    QComboBox *xValues;
    QComboBox *yValues;
    QComboBox *zValues;
    QComboBox *lineTypeCombo;
    
    QLabel    *modelComboLabel;
    QLabel    *datasetComboLabel;
    QLabel    *xComboLabel;
    QLabel    *yComboLabel;
    QLabel    *zComboLabel;
    QLabel    *lineTypeLabel;
  
    QLabel    *xMinLabel;
    QLabel    *xMaxLabel;
    QLabel    *yMinLabel;
    QLabel    *yMaxLabel;
    QLabel    *zMinLabel;
    QLabel    *zMaxLabel;
  
    QDoubleSpinBox *xMinSpin;
    QCheckBox      *xMinAuto;
    QDoubleSpinBox *xMaxSpin;
    QCheckBox      *xMaxAuto;
    QDoubleSpinBox *yMinSpin;
    QCheckBox      *yMinAuto;
    QDoubleSpinBox *yMaxSpin;
    QCheckBox      *yMaxAuto;
    QDoubleSpinBox *zMinSpin;
    QCheckBox      *zMinAuto;
    QDoubleSpinBox *zMaxSpin;
    QCheckBox      *zMaxAuto;
    
    QPushButton *okButton;
    QPushButton *cancelButton;

    void clear();
    
  private slots:
    void okClicked();
    void cancelClicked();
    void showEvent(QShowEvent *event);
    void updateDatasets(int model);
};

#endif

