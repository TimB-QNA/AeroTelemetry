// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include <QtXml>
#include <math.h>

#include "pluginInterfaces.h"
#include "importDialog.h"
#include "selectModelDialog.h"
#include "mainWindow.h"
#include "gfxDisplay.h"

extern QList<networkInterface*> network;

mainWindow::mainWindow(QMainWindow *parent){
  int i;

  // Setup GUI
  vtkWidget = new gfxDisplay();
  setCentralWidget(vtkWidget);

  sessionSettings = new settings(vtkWidget);
  
  // Setup menus
  fileMenu = menuBar()->addMenu("File");
  loadSessionAction=fileMenu->addAction("&Load Session");
  saveSessionAction=fileMenu->addAction("&Save Session");
  importMenu = fileMenu->addMenu("Import Data");
  importDataAction = importMenu->addAction("From delimited data file");
  exitAction=fileMenu->addAction("E&xit");
  
  connect(loadSessionAction, SIGNAL(activated()), this, SLOT(loadSession()));
  connect(saveSessionAction, SIGNAL(activated()), this, SLOT(saveSession()));
  connect(importDataAction,  SIGNAL(activated()), this, SLOT(importDataFromCSV()));
  connect(exitAction,        SIGNAL(activated()), this, SLOT(close()));

  viewMenu = menuBar()->addMenu("View");
  addDockedGraphAction=viewMenu->addAction("Add docked graph");
  connect(addDockedGraphAction, SIGNAL(activated()), this, SLOT(addDockedGraph()));
  
  toolMenu = menuBar()->addMenu("Tools");
  connectAllNetAction   =toolMenu->addAction("Connect All Networks");
  disconnectAllNetAction=toolMenu->addAction("Disconnect All Networks");
  settingsAction=toolMenu->addAction("&Settings");
  connect(settingsAction, SIGNAL(activated()), sessionSettings, SLOT(show())); 
  for (i=0;i<network.count();i++){
    connect(connectAllNetAction,    SIGNAL(activated()), network[i]->asQObject(), SLOT(connectToPeer()));
    connect(disconnectAllNetAction, SIGNAL(activated()), network[i]->asQObject(), SLOT(disconnectFromPeer()));
    connect(network[i]->asQObject(), SIGNAL(addGfxObjectToModel(QString, QString, double, double, double, double)), this, SLOT(addGfxObjectToModel(QString, QString, double, double, double, double)));
    connect(network[i]->asQObject(), SIGNAL(position(QString, double, double, double)), this, SLOT(updateModelPosition(QString, double, double, double)));
    connect(network[i]->asQObject(), SIGNAL(rotation(QString, double, double, double)), this, SLOT(updateModelRotation(QString, double, double, double)));
  }
  
  // Setup view toolbar
  viewToolbar = addToolBar("View");
  viewToolbar->setObjectName("viewToolbar");
  viewCombo   = new QComboBox();
  viewToolbar->addWidget(viewCombo);
  viewStoreAction=viewToolbar->addAction("Store View");
  connect(viewCombo, SIGNAL(currentIndexChanged(QString)), sessionSettings, SLOT(setView(QString)));
  connect(viewStoreAction, SIGNAL(activated()), sessionSettings, SLOT(storeView()));

  navToolbar = new navigationToolbar(addToolBar("Navigation"));
  connect(navToolbar, SIGNAL(timeIndexChanged(int)), this, SLOT(updateModelGuiData(int)));
  statBar=statusBar();
//  statusLabel = new QLabel("");
  for (i=0;i<network.count();i++){
//    statBar->addWidget(statusLabel);
    statBar->addWidget(network[i]->statusIndicator());
    
  }
}

void mainWindow::loadSession(QString fileName){
  int erl, erc, i, nNodes;
  QDomNode node, node2;
  QDomElement root, element, element2;
  QString errMsg;
  QFile file;

  if (fileName.isEmpty()) fileName = QFileDialog::getOpenFileName(this, tr("Load Session"), ".", tr("Session Files (*.mdx)"));
  if (fileName.isEmpty()) return;

  file.setFileName(fileName);
  if (!file.open( QIODevice::ReadOnly )){
    printf("ModelDisplay :: Could not open XML file - %s\n",fileName.toAscii().data());
    return;
  }

  QDomDocument doc( "sessionFile" );
  if (!doc.setContent( &file, false, &errMsg, &erl, &erc)){
    printf("ModelDisplay :: Error at line %i, Column %i - %s\n", erl, erc,errMsg.toAscii().data());
    file.close();
    return;
  }
  file.close();

  root=doc.documentElement();
  if (root.tagName().toLower() != "modeldisplay"){
    printf("ModelDisplay :: This is not a ModelDisplay XML file\n");
    return;
  }

  QProgressDialog progress("Loading Session...", "Cancel", 0, root.childNodes().count(), this);
  progress.setWindowModality(Qt::WindowModal);

  nNodes=0;
  node=root.firstChild();
  while (!node.isNull()){
    progress.setValue(nNodes);
    element=node.toElement();
    if (element.tagName().toLower()=="settings"){
      if (element.attribute("ignore").toLower()!="false") sessionSettings->readXML(node);
    }
    if (element.tagName().toLower()=="model"){
      if (element.attribute("ignore").toLower()!="false"){
        testModel.append(new modelData(vtkWidget));
        testModel.back()->readXML(node);
      }
    }
    if (element.tagName().toLower()=="mainwindow"){
      node2=node.firstChild();
      while (!node2.isNull()){
        element2=node2.toElement();
        if (element2.tagName().toLower()=="dockwidget") addDockedWidget(node2);
        if (element2.tagName().toLower()=="state"){
          if (element2.attribute("encoding").toLower()=="base64"){
            restoreState(QByteArray::fromBase64(element2.text().toAscii()));
          }
        }
        node2=node2.nextSibling();
      }
    }
    node=node.nextSibling();
    nNodes++;
  }

  // Setup GUI for session
  viewCombo->clear();
  viewCombo->addItems(sessionSettings->viewsAvailable());
  vtkWidget->runRenderer();
}

void mainWindow::importDataFromCSV(){
  int mIdx=-1;
  if (testModel.size()==0){
    statBar->showMessage(QString("No model to import data into"),5000);
    return;
  }
//  if (testModel.size()==1) mIdx=0;
//  if (testModel.size()>1){
    selectModelDialog *sMDia = new selectModelDialog();
    sMDia->models=testModel;
    sMDia->exec();
    mIdx=sMDia->mIndex;
//  }
  if (mIdx!=-1){
    importDialog *iDia = new importDialog();
    iDia->fileName = QFileDialog::getOpenFileName(this, tr("Import dataset"), ".", tr("Data Files (*.csv)"));
    iDia->dataset=&testModel[0]->sampleData;
    iDia->exec();
  }
  if (testModel[0]->sampleData.size()==0){
    statBar->showMessage(QString("Dataset was not loaded"),5000);
    return;
  }
}

void mainWindow::saveSession(){
  int i, j;
  QFile file;
  QString fileName;
  QStringList tempData;
  
  fileName = QFileDialog::getSaveFileName(this, tr("Save Session File"), ".", tr("Session Files (*.mdx)"));
  if (fileName.isEmpty()) return;

  file.setFileName(fileName);
  if (!file.open( QIODevice::WriteOnly | QIODevice::Text )){
    printf("ModelDisplay :: Could not open file to save session - %s\n",fileName.toAscii().data());
    return;
  }

  QTextStream out(&file);
  out << "<modelDisplay>\n";
  tempData=sessionSettings->writeXML();
  for (i=0;i<tempData.count();i++) out << "  " << tempData[i] << "\n";

  for (j=0;j<testModel.count();j++){
    tempData=testModel[j]->writeXML();
    for (i=0;i<tempData.count();i++) out << "  " << tempData[i] << "\n";
  }
  
  out << "  <mainWindow>\n";
  for (j=0;j<dockWidget.count();j++){
    out << "    <dockWidget>\n";
    out << "      <objectName>" << dockWidget[j]->objectName() << "</objectName>\n";
    // Find widget related to dock Window...
    for (i=0;i<graph.count();i++){
      if (graph[i]==dockWidget[j]->widget()){
        tempData=graph[i]->writeXML();
        break;
      }
    }
    for (i=0;i<tempData.count();i++) out << "        " << tempData[i] << "\n";
    out << "    </dockWidget>\n";
  }
  out << "    <state encoding='base64'>" << saveState().toBase64() << "</state>\n";
  out << "  </mainWindow>\n";
  out << "</modelDisplay>\n";
  
  file.close();
}

void mainWindow::addGfxObjectToModel(QString body, QString type, double x, double y, double z, double size){
  int i;
  if (type.toLower()=="sphere"){
//    printf("Looking for body to add ball to\n");
    for (i=0;i<testModel.count();i++){
//      printf("  Looking for .%s.    -    Found .%s.\n",testModel[i]->name.toLower().toAscii().data(), body.toLower().toAscii().data());
      if (testModel[i]->name.toLower()==body.toLower()){
//        printf("    Found body - adding ball\n");
//        printf("    Radius=%lf\n",size/2.);
        testModel[i]->addUserSphere(x, y, z, size/2.);
      }
    }
  }
}

void mainWindow::updateModelPosition(QString body, double x, double y, double z){
  int i;
  for (i=0;i<testModel.count();i++){
    if (testModel[i]->name.toLower()==body.toLower()) testModel[i]->updatePosition(x,y,z);
  }
  vtkWidget->runRenderer();
}

void mainWindow::updateModelRotation(QString body, double x, double y, double z){
  int i;
  for (i=0;i<testModel.count();i++){
    if (testModel[i]->name.toLower()==body.toLower()) testModel[i]->updateRotation(x,y,z);
  }
  vtkWidget->runRenderer();
}

void mainWindow::updateModelGuiData(int index){
  int i;
  for (i=0;i<testModel.count();i++){
    testModel[i]->updateGraphics(index);
  }
}

void mainWindow::addDockedGraph(){
  QDomDocument spec;
  spec.setContent(QString("<dockWidget><graph></graph></dockWidget>"));
  addDockedWidget(spec.documentElement());
}

void mainWindow::addDockedWidget(QDomNode root){
  dockWidget.append(new QDockWidget());
  dockWidget.back()->setObjectName(QString("dock%1").arg(dockWidget.size()-1));

  QDomNode node;
  QDomElement element;
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="objectname") dockWidget.back()->setObjectName(element.text());
    if (element.tagName().toLower()=="graph"){
      graph.append(new graphPlot(&testModel));
      graph.back()->readXML(node);
      dockWidget.back()->setWidget(graph.back());
    }
    node=node.nextSibling();
  }
  addDockWidget(Qt::LeftDockWidgetArea, dockWidget.back());
}