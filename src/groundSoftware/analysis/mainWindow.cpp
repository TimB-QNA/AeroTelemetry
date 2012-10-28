// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include <math.h>
#include "telemetryData.h"
#include "mainWindow.h"
#include "importDialog.h"

extern telemetryData dataset;

mainWindow::mainWindow(QMainWindow *parent) : QMainWindow(parent){
  mdiArea = new QMdiArea;
  mdiArea->setContextMenuPolicy(Qt::ActionsContextMenu);
//  mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//  mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  setCentralWidget(mdiArea);

  newGraphAction = new QAction("New Graph",this);
  newVideoAction = new QAction("New Video Display",this);
  mdiArea->addAction(newGraphAction);
  mdiArea->addAction(newVideoAction);

  fileMenu = menuBar()->addMenu("File");
  newDataAction  = fileMenu->addAction("New Dataset");
  openDataAction = fileMenu->addAction("Open Dataset");
  saveDataAction = fileMenu->addAction("Save Dataset");
  fileMenu->addSeparator();
  importMenu = fileMenu->addMenu("Import Data");
  importDataAction = importMenu->addAction("From data file");
  exitAction = fileMenu->addAction("Exit");

  connect(openDataAction,   SIGNAL(activated()), this, SLOT(loadData()));
  connect(saveDataAction,   SIGNAL(activated()), this, SLOT(saveData()));
  connect(importDataAction, SIGNAL(activated()), this, SLOT(importDataFromCSV()));
  
  connect(newGraphAction,   SIGNAL(activated()), this, SLOT(createNewGraphWindow()));
  
  // create status bar
  statusBar();
}

void mainWindow::importDataFromCSV(){
  importDialog *iDia = new importDialog();
  iDia->fileName = QFileDialog::getOpenFileName(this, tr("Import dataset"), ".", tr("Data Files (*.csv)"));
  iDia->dataset=&dataset;
  iDia->exec();
  if (dataset.size()==0){
    statusBar()->showMessage(QString("Dataset was not loaded"),5000);
  }
  updatePlots();
}

void mainWindow::loadData(){
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open dataset"), ".", tr("Data Files (*.atd)"));
  dataset.readXML(fileName);
  updatePlots();
}

void mainWindow::saveData(){
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save dataset"), ".", tr("Data Files (*.atd)"));
  dataset.writeXML(fileName);
}

void mainWindow::createNewGraphWindow(){
  QList<QMdiSubWindow*> subWinList;

  mdiSubWindows.append(new QMdiSubWindow());
  mdiPlots.append(new mdiPlot(this));

  mdiSubWindows.last()->setWindowTitle(QString("Graph Window %1").arg(mdiPlots.size()));
  mdiSubWindows.last()->setWidget(mdiPlots.last());
  mdiArea->addSubWindow(mdiSubWindows.last());
  mdiSubWindows.last()->show();
}

void mainWindow::updatePlots(){
  int i;
  QStringList script;
  char line[4096];
  
  script.append("plot '-' with lines title 'X Acc', '-' with lines title 'Y Acc', '-' with lines title 'Z Acc'");
  for (i=0;i<dataset.size();i++){
    sprintf(line,"%llg %lf",dataset.datapoint[i].time, dataset.datapoint[i].accX); script.append(line);
  }
  script.append("e");
  for (i=0;i<dataset.size();i++){
    sprintf(line,"%llg %lf",dataset.datapoint[i].time, dataset.datapoint[i].accY); script.append(line);
  }
  script.append("e");
  for (i=0;i<dataset.size();i++){
    sprintf(line,"%llg %lf",dataset.datapoint[i].time, dataset.datapoint[i].accZ); script.append(line);
  }
  script.append("e");
//  imuPlot->plotgraph(script);

  script.clear();
  script.append("plot '-' with lines title 'Speed'");
  for (i=0;i<dataset.size();i++){
    sprintf(line,"%llg %lf",dataset.datapoint[i].time, dataset.datapoint[i].speed); script.append(line);
  }
  script.append("e");
//  speedPlot->plotgraph(script);
}