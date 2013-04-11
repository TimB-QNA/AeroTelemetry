// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include "modelDataSettingsDialog.h"

modelDataSettingsDialog::modelDataSettingsDialog(modelData *modData, QDialog *parent) : QDialog(parent) {
  int i;
  QStringList pluginNames;
  QList<QWidget*> panels;
  model=modData;
  
  QGridLayout *smplLayout = new QGridLayout();

  tabs = new QTabWidget();
  panels=model->settings.panelList();
  pluginNames=model->settings.pluginNames();
  for (i=0;i<panels.count();i++){
    tabs->addTab(panels[i],pluginNames[i]);
  }
  smplLayout->addWidget(tabs,0,0,1,-1);

      ok = new QPushButton("Ok");
  cancel = new QPushButton("Cancel");
  
  smplLayout->addWidget(ok    ,1,2);
  smplLayout->addWidget(cancel,1,3);

  setLayout(smplLayout);
  
  connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void modelDataSettingsDialog::showEvent(QShowEvent *event){
  int i;
  model->settings.showEvent(event);
}

void modelDataSettingsDialog::okClicked(){

}