#ifndef mainWindow_H
  #define mainWindow_H

#include <QtGui>
#include "gfxDisplay.h"
#include "modelData.h"
#include "settings.h"
#include "pluginInterfaces.h"
#include "navigationToolbar.h"
#include "graphPlot.h"

class mainWindow : public QMainWindow
{
   Q_OBJECT

  public:
    mainWindow(QMainWindow *parent=0);

  public slots:
    void loadSession(QString fileName="");
    
  private:
    gfxDisplay *vtkWidget;
    QList<modelData*> testModel;
    settings *sessionSettings;

    // File Menu Entries
    QMenu *fileMenu;
    QAction *loadSessionAction;
    QAction *saveSessionAction;
    QAction *exitAction;

    // Import sub-menu
    QMenu *importMenu;
    QAction *importDataAction;

    // View menu entries
    QMenu *viewMenu;
    QAction *addDockedGraphAction;
  
    // Tool Menu Entries
    QMenu *toolMenu;
    QAction *settingsAction;
    QAction *connectAllNetAction;
    QAction *disconnectAllNetAction;
    
    // View tool bar
    QToolBar *viewToolbar;
    QComboBox *viewCombo;
    QAction *viewStoreAction;

    navigationToolbar *navToolbar;
    
    QStatusBar *statBar;
    QLabel *statusLabel;

    QList<QDockWidget*> dockWidget;
    QList<graphPlot*> graph;

    void addDockedWidget(QDomNode root);
    
  private slots:
    void saveSession();
    void importDataFromCSV();
    void addGfxObjectToModel(QString body, QString type, double x, double y, double z, double size);
    void updateModelPosition(QString body, double x, double y, double z);
    void updateModelRotation(QString body, double x, double y, double z);
    void updateModelGuiData(int index);
    void addDockedGraph();
};

#endif

