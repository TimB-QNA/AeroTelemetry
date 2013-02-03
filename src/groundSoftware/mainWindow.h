#ifndef mainWindow_H
  #define mainWindow_H

#include <QtGui>
#include "gfxDisplay.h"
#include "modelData.h"
#include "settings.h"
#include "pluginInterfaces.h"

class mainWindow : public QMainWindow
{
   Q_OBJECT

  public:
    mainWindow(QMainWindow *parent=0);
    
  private:
    gfxDisplay *vtkWidget;
    QList<modelData*> testModel;
    settings *sessionSettings;

    // File Menu Entries
    QMenu *fileMenu;
    QAction *loadSessionAction;
    QAction *saveSessionAction;
    QAction *exitAction;

    // Tool Menu Entries
    QMenu *toolMenu;
    QAction *settingsAction;
    QAction *connectAllNetAction;
    QAction *disconnectAllNetAction;
    
    // View tool bar
    QToolBar *viewToolbar;
    QComboBox *viewCombo;
    QAction *viewStoreAction;

    QStatusBar *statBar;
    
  private slots:
    void loadSession();
    void saveSession();
    void addGfxObjectToModel(QString body, QString type, double x, double y, double z, double size);
    void updateModelPosition(QString body, double x, double y, double z);
    void updateModelRotation(QString body, double x, double y, double z);
};

#endif

