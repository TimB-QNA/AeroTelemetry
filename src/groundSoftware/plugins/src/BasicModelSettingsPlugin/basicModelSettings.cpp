#include "basicModelSettings.h"

Q_EXPORT_PLUGIN2(basicModelSettings, basicModelSettings);

basicModelSettings::basicModelSettings(QObject *parent) : QObject(parent){
  modelName="un-named";
  
  panel = new QWidget();

  QGridLayout *smplLayout = new QGridLayout();

  nameLabel = new QLabel("Model Name");
  nameBox   = new QLineEdit(); nameBox->setText(modelName);
  smplLayout->addWidget(nameLabel,0,0);
  smplLayout->addWidget(nameBox,0,1,1,-1);

  geomFileLabel = new QLabel("Geometry File");
  geomFileBox   = new QLineEdit();
  geomBrowseButton = new QPushButton("Browse");
  smplLayout->addWidget(geomFileLabel,1,0);
  smplLayout->addWidget(geomFileBox,1,1,1,2);
  smplLayout->addWidget(geomBrowseButton,1,3);
  vtkWidget = new gfxDisplay();
  vtkWidget->setMinimumSize(150,150);
  smplLayout->addWidget(vtkWidget,2,0,1,-1);

  panel->setLayout(smplLayout);

  connect(geomBrowseButton, SIGNAL(clicked()), this, SLOT(browseClicked()));
}

QObject* basicModelSettings::asQObject(){
  return this;
}

QString basicModelSettings::pluginName(){
  return QString("BasicModelSettings");
}

QString basicModelSettings::pluginDescription(){
  return QString("Provides settings common to any type of model.");
}

QString basicModelSettings::xmlRootTag(){
  return QString("basicSettings");
}

void basicModelSettings::readXML(QDomNode root){
  QDomNode node;
  QDomElement element;
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="modelname") modelName=element.text();
    if (element.tagName().toLower()=="geometryfile") geometryFile=element.text();
    node=node.nextSibling();
  }
}

QStringList basicModelSettings::writeXML(){
  QStringList xmlOut;
  xmlOut.append("<"+xmlRootTag()+">");
  xmlOut.append("<modelName>"+modelName+"</modelName>");
  xmlOut.append("<geometryFile>"+geometryFile+"</geometryFile>");
  xmlOut.append("</"+xmlRootTag()+">");
  return xmlOut;
}

QWidget* basicModelSettings::settingsPanel(){
//  nameBox->setText(modelName);
//  geomFileBox->setText(geometryFile);
//  vtkWidget->loadModel(geometryFile);
  return panel;
}

void basicModelSettings::storeSettings(){
  modelName=nameBox->text();
  geometryFile=geomFileBox->text();
  //createGfxObject(geometryFile);
}

void basicModelSettings::browseClicked(){
  QString fileName = QFileDialog::getOpenFileName(0,
     tr("Open Geometry"), ".", tr("Geometry Files (*.3dm)"));

  if (!fileName.isEmpty()){
    geomFileBox->setText(fileName);
    vtkWidget->clear();
    vtkWidget->loadModel(fileName);
  }
}

void basicModelSettings::showEvent(QShowEvent *event){
  nameBox->setText(modelName);
  geomFileBox->setText(geometryFile);
  vtkWidget->loadModel(geometryFile);
}


QVariant basicModelSettings::get(QString settingName){
  int i;
  QVariant result;
  QStringList hierarchy;

//  printf("Setting Request: %s\n",settingName.toAscii().data());
  
  hierarchy=settingName.split(".");
//  for (i=0;i<hierarchy.count();i++){
//    printf("part[%i] = %s\n",i,hierarchy[i].toAscii().data());
//  }
  // ignore if it's a badly-formed request.
  if (hierarchy.count()<2) return QVariant();
  // ignore if the first part of the hierarchy doesn't look like one of ours.
  if (hierarchy[0].toLower()!=xmlRootTag().toLower()) return QVariant();

  // By this point we know it's one we can handle, therefore,,,
  if (hierarchy[1].toLower()=="modelname") result=QVariant(modelName);
  if (hierarchy[1].toLower()=="geometryfile") result=QVariant(geometryFile);

//  printf("Returning %s\n",result.toString().toAscii().data());
  return result;
}