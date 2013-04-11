#ifndef modelDataEditPage_H
  #define modelDataEditPage_H

#include <QtGui>
#include "gfxDisplay.h"
#include "modelData.h"

class modelDataSettingsDialog : public QDialog
{
  Q_OBJECT

  public:
    modelDataSettingsDialog(modelData *modData, QDialog *parent=0);
    modelData *model;
    
  private:
    QTabWidget *tabs;
    
    QPushButton *ok;
    QPushButton *cancel;
    
  private slots:
    void okClicked();
    void showEvent(QShowEvent *event);
};

#endif