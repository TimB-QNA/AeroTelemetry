#ifndef importDialog_H
  #define importDialog_H

#include <QtGui>
#include "telemetryData.h"

class importDialog : public QDialog
{
   Q_OBJECT

  public:
    importDialog(QDialog *parent=0);
    QString fileName;
    telemetryData *dataset;
    
  private:
    QGridLayout *mainLayout;
    QGridLayout *dataLayout;
    QLabel    *smplLbl;
    QTextEdit *smplBox;
    QLabel    *modeLbl;
    QLabel    *sepLbl;    
    QComboBox *modeBox;
    QComboBox *sepBox;
    QLabel    *headLbl;
    QSpinBox  *headSpin;
  
    QStringList dataName;
    QList<QLabel*> dataLabel;
    QList<QComboBox*> dataCombo;
    QList<QComboBox*> unitsCombo;

    QPushButton *ok;
    QPushButton *cancel;

    QStringList sampleData;
    
    void showEvent(QShowEvent *event);
    
  private slots:
    void updateOptions();
    void readData();
};

#endif

