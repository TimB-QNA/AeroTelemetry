#ifndef editModelsDialog_H
  #define editModelsDialog_H

#include <QtGui>
#include "modelData.h"

class editModelsDialog : public QDialog
{
   Q_OBJECT

  public:
    editModelsDialog(QList<modelData*> *data, gfxDisplay *gfx, QDialog *parent=0);
    
  private:
    QList<modelData*> *modelList;  // Existing model list.
    gfxDisplay  *mainVtkWidget; // VTK Widget in main window.
    QPushButton *ok;
    QPushButton *cancel;
    QPushButton *createModelButton;
    QPushButton *editModelButton;
    QListWidget *modelBox;
    
  private slots:
    void createModel();
    void editModel();
    void showEvent(QShowEvent *event);
};

#endif

