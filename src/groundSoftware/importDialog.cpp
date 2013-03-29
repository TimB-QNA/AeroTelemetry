// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include "importDialog.h"
#include "telemetryDataPoint.h"

importDialog::importDialog(QDialog *parent) : QDialog(parent){
  QGridLayout *smplLayout = new QGridLayout();
  QGridLayout *modeLayout = new QGridLayout();
  QGridLayout *optLayout = new QGridLayout();

  mainLayout = new QGridLayout();
  // prep data layout but don't populate it until updateOptions
  dataLayout = new QGridLayout();
  
  smplLbl  = new QLabel("Sample Data");
  smplBox  = new QTextEdit(this);
  smplLayout->addWidget(smplLbl,0,0);
  smplLayout->addWidget(smplBox,1,0);

  smplBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  smplBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  
  modeLbl  = new QLabel("Data Mode");
  sepLbl   = new QLabel("Data Separator");
  modeBox  = new QComboBox(this);
  sepBox   = new QComboBox(this);
  headLbl  = new QLabel("Header Lines");
  headSpin = new QSpinBox(this);
    
  modeBox->addItem("Columns");
//  modeBox->addItem("Rows");
  modeBox->setCurrentIndex(0);
  
  sepBox->addItem("Any WhiteSpace");
  sepBox->addItem("Space");
  sepBox->addItem("Tab");
  sepBox->addItem("Comma");
  sepBox->addItem("Semicolon");
  sepBox->setCurrentIndex(0);

  headSpin->setMinimum(0);
  headSpin->setMaximum(50);
  
  modeLayout->addWidget(modeLbl ,0,0);
  modeLayout->addWidget(modeBox ,0,1);
  modeLayout->addWidget(sepLbl  ,0,2);
  modeLayout->addWidget(sepBox  ,0,3);
  modeLayout->addWidget(headLbl ,0,4);
  modeLayout->addWidget(headSpin,0,5);

  ok     = new QPushButton("Ok");
  cancel = new QPushButton("Cancel");
  optLayout->addWidget(ok,0,5);
  optLayout->addWidget(cancel,0,6);
  
  mainLayout->addLayout(smplLayout,0,0);
  mainLayout->addLayout(modeLayout,1,0);
  mainLayout->addLayout(dataLayout,2,0);
  mainLayout->addLayout(optLayout, 3,0);
  setLayout(mainLayout);
  connect(modeBox,  SIGNAL(currentIndexChanged(int)), this, SLOT(updateOptions()));
  connect(sepBox,   SIGNAL(currentIndexChanged(int)), this, SLOT(updateOptions()));
  connect(headSpin, SIGNAL(valueChanged(int)),        this, SLOT(updateOptions()));
  connect(ok,       SIGNAL(clicked()),                this, SLOT(readData()));
  connect(cancel,   SIGNAL(clicked()),                this, SLOT(reject()));
}

void importDialog::showEvent(QShowEvent *event){
  int i;
  
  QFile inputFile(fileName);

  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) return;

  i=0;
  // Keep max i value greater than number of comment lines.
  // This reduces code in updateOptions()
  while (!inputFile.atEnd() && i<51){
    sampleData.append(inputFile.readLine());
    i++;
  }
  inputFile.close();
  updateOptions();
}

void importDialog::updateOptions(){
  int i, j, k, nCols;
  telemetryDataPoint tdp;
  QRegExp rx;
  QStringList entry, entryLine;

  // Set regular expression for split based on option.
  if (sepBox->currentIndex()==0) rx.setPattern("\\s");
  if (sepBox->currentIndex()==1) rx.setPattern(" ");
  if (sepBox->currentIndex()==2) rx.setPattern("\\t");
  if (sepBox->currentIndex()==3) rx.setPattern(",");
  if (sepBox->currentIndex()==4) rx.setPattern(";");
  
//  smplBox->setText(sampleData.join(""));
  if (modeBox->currentIndex()==0){
    // Work on column-based values
    for (i=0;i<sampleData.size();i++){
      entryLine=sampleData[i].split(rx,QString::KeepEmptyParts);
      entryLine.pop_back();
      if (i<headSpin->value()){
        entryLine.prepend("<font color='grey'>");
        entryLine.append("</font>");
        entry.append(entryLine.join("<font color='dark blue'>|</font>"));
      }else{
        entry.append(entryLine.join("<font color='red'>|</font>"));
      }
    }
  }
  smplBox->setHtml(entry.join("<br>"));

  // Count number of columns on the first non-comment line...
  entryLine=sampleData[headSpin->value()].split(rx,QString::KeepEmptyParts);
  entryLine.pop_back();
  nCols=entryLine.size();

  // Clear layout prior to rebuilding. Note this loses data
  while (dataLayout->takeAt(0) != 0){ }
  for (i=0;i<dataLabel.size();i++){
    delete dataLabel[i];
    delete dataCombo[i];
    delete unitsCombo[i];
  }
  dataLabel.clear(); dataCombo.clear(); unitsCombo.clear();
  
  // Create combo boxes etc and put in layout.
  j=0; k=0;
  for (i=0;i<nCols;i++){
    dataLabel.append(new QLabel(QString("Column %1").arg(i)));
    dataCombo.append(new QComboBox(this));
    unitsCombo.append(new QComboBox(this));

    dataCombo[i]->addItems(tdp.fieldList);
    unitsCombo[i]->addItems(tdp.unitList);
    if (j==15){
      k+=3;
      j=0;
    }
    dataLayout->addWidget(dataLabel[i],j,k+0);
    dataLayout->addWidget(dataCombo[i],j,k+1);
    dataLayout->addWidget(unitsCombo[i],j,k+2);
    j++;
  }
  
}

void importDialog::readData(){
  int i;
  telemetryDataPoint tdp;
  QList<int> fieldList, unitList;
  QRegExp rx;
  
  // Set regular expression for split based on option.
  if (sepBox->currentIndex()==0) rx.setPattern("\\s");
  if (sepBox->currentIndex()==1) rx.setPattern(" ");
  if (sepBox->currentIndex()==2) rx.setPattern("\\t");
  if (sepBox->currentIndex()==3) rx.setPattern(",");
  if (sepBox->currentIndex()==4) rx.setPattern(";");

  for (i=0;i<dataCombo.size();i++){
    fieldList.append(tdp.fieldIndex(dataCombo[i]->currentText()));
     unitList.append(tdp.unitIndex(unitsCombo[i]->currentText()));
  }
  
  dataset->importFromFile(fileName, rx, fieldList, unitList, headSpin->value());
  close();
}