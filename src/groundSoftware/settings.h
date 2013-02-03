#ifndef settings_H
  #define settings_H

#include <QtGui>
#include <QtXml>
#include "gfxDisplay.h"
#include "modelData.h"
#include "viewSettings.h"

class settings : public QDialog
{
   Q_OBJECT

  public:  
    settings(gfxDisplay *d, QDialog *parent=0);
    void readXML(QDomNode root);
    QStringList writeXML();    
    QStringList viewsAvailable();

  public slots:
    void storeView();
    void setView(QString vName);
    
  private:
    int currentView;
    QString sceneryFile;
    gfxDisplay *display;
    QList<viewSettings> view;

    // GUI parts
    QTabWidget *tabWidget;
};

#endif

