#ifndef selectModelDialog_H
  #define selectModelDialog_H

#include <QtGui>
#include "modelData.h"

class selectModelDialog : public QDialog
{
   Q_OBJECT

  public:
    int mIndex;
    QList<modelData*> models;
    selectModelDialog(QDialog *parent=0);
    
  private:
    QLabel *modelLabel;
    QComboBox *modelBox;
    QPushButton *previewButton;
  
    QPushButton *okButton;
    QPushButton *cancelButton;

    void showEvent(QShowEvent *event);
    
  private slots:
    void readData();
};

#endif

