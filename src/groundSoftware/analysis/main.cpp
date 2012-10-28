// RST Racing
//
// Telemetry & Control system
//
// Host code

#include <QApplication>
#include "mainWindow.h"
#include "telemetryData.h"

telemetryData dataset;

int main(int argc, char * argv[]){
  int rVal;
  mainWindow *window;
  QApplication app(argc,argv);
  app.setApplicationName("RST Telemetry");
  
  window = new mainWindow;
  window->show();
  return app.exec();
}
