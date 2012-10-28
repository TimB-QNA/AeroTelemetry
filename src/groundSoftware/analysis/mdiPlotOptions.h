/*
    Description: Provide Gnuplot graphs for QT4 (Class Header)
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/

#ifndef mdiPlotOptions_H
  #define mdiPlotOptions_H

#include <QtGui>
#include <QtDesigner/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT mdiPlotOptions : public QDialog
{
   Q_OBJECT
   
  public:
    mdiPlotOptions(QDialog *parent=0);
    void print();

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
    QComboBox *xValues;
    QComboBox *yValues;
    QComboBox *zValues;
    QComboBox *lineTypeCombo;
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
};

#endif

