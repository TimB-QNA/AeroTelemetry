#ifndef mainWindow_H
  #define mainWindow_H

#include <QtGui>
#include <qt4gnuplot.h>
#include <gauge.h>
#include "videoDisplay.h"
#include "mdiPlot.h"

class mainWindow : public QMainWindow
{
   Q_OBJECT

  public:
    mainWindow(QMainWindow *parent=0);
       
  private:
    QMdiArea      *mdiArea;
    QList<QMdiSubWindow*> mdiSubWindows;
    QList<mdiPlot*> mdiPlots;
    
    QAction       *newGraphAction;
    QAction       *newVideoAction; 
    
    
    qt4gnuplot    *imuPlot;
    qt4gnuplot    *speedPlot;
    QLabel        *gpsPlot;
    videoDisplay  *camImage;
//    QTimer        *plotTimer;
    QSplitter *mainSplit;
    QSplitter *imuCamSplit;
    QSplitter *speedGpsSplit;

    QMenu *fileMenu;
    QAction *newDataAction;
    QAction *openDataAction;
    QAction *saveDataAction;
    
    QMenu *importMenu;
    QAction *importDataAction;
    QAction *exitAction;
    
  private slots:
    void importDataFromCSV();
    void saveData();
    void loadData();
    void createNewGraphWindow();
    void updatePlots();
};

#endif

