// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include "editModelsDialog.h"
#include "modelDataSettingsDialog.h"

editModelsDialog::editModelsDialog(QList<modelData*> *data, gfxDisplay *gfx, QDialog *parent) : QDialog(parent){
  QGridLayout *smplLayout = new QGridLayout();

  modelList = data;
  mainVtkWidget = gfx;
  createModelButton = new QPushButton("Add");
  smplLayout->addWidget(createModelButton,7,0);
  editModelButton = new QPushButton("Edit");
  smplLayout->addWidget(editModelButton,7,1);

  modelBox = new QListWidget();
  smplLayout->addWidget(modelBox,0,0,6,-1);
  ok     = new QPushButton("Ok");
  cancel = new QPushButton("Cancel");
  smplLayout->addWidget(ok,7,3);
  smplLayout->addWidget(cancel,7,4);
  setLayout(smplLayout);
  
//  connect(geomBrowseButton, SIGNAL(clicked()), this, SLOT(browseClicked()));
  connect(createModelButton, SIGNAL(clicked()), this, SLOT(createModel()));
  connect(editModelButton, SIGNAL(clicked()), this, SLOT(editModel()));
//  connect(ok,               SIGNAL(clicked()), this, SLOT(okClicked()));
  connect(cancel,            SIGNAL(clicked()), this, SLOT(reject()));
}

void editModelsDialog::showEvent(QShowEvent *event){
  int i;
  modelBox->clear();
  for (i=0;i<modelList->count();i++){
    modelBox->addItem(modelList->at(i)->settings.get("basicSettings.modelName").toString());
  }
}

void editModelsDialog::createModel(){
  modelDataSettingsDialog *dialog;
  modelData *tempModel;
  tempModel = new modelData(mainVtkWidget);
  dialog = new modelDataSettingsDialog(tempModel);
  dialog->show();
  modelList->append(tempModel);
}

void editModelsDialog::editModel(){
  int index;
  modelDataSettingsDialog *dialog;

  index=modelBox->currentRow();
  if (index>=0 && index<modelList->count()){
    dialog = new modelDataSettingsDialog(modelList->at(index));
    dialog->show();
  }
}