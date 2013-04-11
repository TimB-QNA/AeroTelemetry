// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include "selectModelDialog.h"

selectModelDialog::selectModelDialog(QDialog *parent) : QDialog(parent){
  QGridLayout *smplLayout = new QGridLayout();

  modelLabel    = new QLabel("Model");        smplLayout->addWidget(modelLabel    ,0,0);
  modelBox      = new QComboBox(this);        smplLayout->addWidget(modelBox      ,0,1);
  previewButton = new QPushButton("Preview"); smplLayout->addWidget(previewButton ,0,2); previewButton->setEnabled(false);
  okButton      = new QPushButton("Ok");      smplLayout->addWidget(okButton      ,1,1);
  cancelButton  = new QPushButton("Cancel");  smplLayout->addWidget(cancelButton  ,1,2);

  setLayout(smplLayout);
  connect(okButton,       SIGNAL(clicked()),                this, SLOT(readData()));
  connect(cancelButton,   SIGNAL(clicked()),                this, SLOT(reject()));
}

void selectModelDialog::showEvent(QShowEvent *event){
  int i;
  mIndex=-1;
  for (i=0;i<models.size();i++){
    modelBox->addItem(models[i]->settings.get("basicSettings.modelName").toString(),i);
  }
}

void selectModelDialog::readData(){
  mIndex=modelBox->itemData(modelBox->currentIndex()).toInt();
  close();
}