// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include "navigationToolbar.h"

navigationToolbar::navigationToolbar(QToolBar *parent) : QObject(parent){
  toolBar=parent;
  parent->setObjectName(toolBar->windowTitle());
  masterData = &defaultTelemetry; // Blank telemetryData structure to prevent segfaults
  
         back = new QPushButton("<");    toolBar->addWidget(back);
     stepBack = new QPushButton("<|");   toolBar->addWidget(stepBack);
         stop = new QPushButton("||");   toolBar->addWidget(stop);
  stepForward = new QPushButton("|>");   toolBar->addWidget(stepForward);
      forward = new QPushButton(">");    toolBar->addWidget(forward);

         back->setCheckable(true);
      forward->setCheckable(true);
      
       divTwo = new QPushButton("/2");        divTwo->setCheckable(true); toolBar->addWidget(divTwo);
     timesTwo = new QPushButton("x2");      timesTwo->setCheckable(true); toolBar->addWidget(timesTwo);
  normalSpeed = new QPushButton("1:1");  normalSpeed->setCheckable(true); toolBar->addWidget(normalSpeed);
  liveFeed    = new QPushButton("Live");    liveFeed->setCheckable(true); toolBar->addWidget(liveFeed);
  
  streamPosition = new QSlider();       toolBar->addWidget(streamPosition);
  streamPosition->setOrientation(Qt::Horizontal);

//  connect(okButton,       SIGNAL(clicked()),                this, SLOT(readData()));
//  connect(cancelButton,   SIGNAL(clicked()),                this, SLOT(reject()));
      
  connect(stepBack,    SIGNAL(clicked()), this, SLOT(updateIndex()));
  connect(stepForward, SIGNAL(clicked()), this, SLOT(updateIndex()));
}

void navigationToolbar::setMasterData(telemetryData *data){
  masterData=data;
  timeIdx=0;
  emit timeIndexChanged(timeIdx);
}

int navigationToolbar::timeIndex(){
  return timeIdx;
}

QDateTime navigationToolbar::time(){
  return masterData->datapoint[timeIdx].time;
}

void navigationToolbar::updateIndex(){
  int intendStep;
  QPushButton *sent = (QPushButton*)sender();

  if (sent==0){
    printf("Bad navigation sender\n");
    return;
  }

  if (sent==stepBack){
    printf("Step Back clicked\n");
    back->setChecked(false);
    forward->setChecked(false);
    liveFeed->setChecked(false);
    intendStep=-1;
  }

  if (sent==stepForward && !liveFeed->isChecked()){
    printf("Step Forward Clicked\n");
    back->setChecked(false);
    stop->setChecked(false);
    forward->setChecked(false);
    liveFeed->setChecked(false);
    intendStep=1;
  }

  timeIdx+=intendStep;
  if (timeIdx<0) timeIdx=0;
  if (timeIdx>=masterData->datapoint.size()) timeIdx=masterData->datapoint.size()-1;
  emit timeIndexChanged(timeIdx);
}