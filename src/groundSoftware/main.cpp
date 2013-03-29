// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QApplication>
#include "mainWindow.h"
#include "projection.h"
void header();

// Network feed plugins...
QList<networkInterface*> network;
projection planet;

int main(int argc, char * argv[]){
  int i;
  header();
  QApplication app(argc,argv);

  printf("Loading plugins:\n");
  // Load plugins...
  networkInterface *netPlugin;
  QDir pluginDir("plugins");
  QStringList pluginFiles;
  pluginDir.setNameFilters(QStringList(QString("*.so")));
  pluginFiles=pluginDir.entryList();
  for (i=0;i<pluginFiles.count();i++){
//    printf("Trying to load - %s\n",pluginFiles[i].toAscii().data());
    QPluginLoader loader(pluginDir.path()+"/"+pluginFiles[i]);
    netPlugin = qobject_cast<networkInterface *> (loader.instance());
    if (netPlugin){
      printf("%s\t-\t%s\n", netPlugin->pluginName().toAscii().data(), netPlugin->pluginDescription().toAscii().data());
      network.append(netPlugin);
    }else{
      printf("Failed to load plugin - %s\n",loader.errorString().toAscii().data());
    }
  }
  
  mainWindow *window = new mainWindow;

  for (i=0;i<argc;i++){
    if (QString(argv[i])=="-i") window->loadSession(argv[i+1]);
  }
  
  window->show();
  
  return app.exec();
}

void header(){
  printf("AeroTelemetry Ground Program\n");
  printf("\n");
  printf("  Version: %s\n", VERSION.toAscii().data());
  printf("   Author: Tim Brocklehurst - timb@engineering.selfip.org\n");
}
