#ifndef basicModelSettings_H
  #define basicModelSettings_H

#include <QtGui>
#include <QtPlugin>
#include "../../../pluginInterfaces.h"
#include "../../../gfxDisplay.h"

class basicModelSettings : public QObject, public modelDataSettingsInterface
{
  Q_OBJECT
  Q_INTERFACES(modelDataSettingsInterface)
  
  public:
    basicModelSettings(QObject *parent=0);
    QObject* asQObject();
    QString pluginName();
    QString pluginDescription();
    QString xmlRootTag();
    void readXML(QDomNode root);
    QStringList writeXML();
    
    QWidget* settingsPanel();
    void storeSettings();
    void showEvent(QShowEvent *event);
    QVariant get(QString settingName);
    
  private:
    QString modelName;
    QString geometryFile;
    QWidget *panel;

    QLabel    *nameLabel;
    QLineEdit *nameBox;
    QLabel    *geomFileLabel;
    QLineEdit *geomFileBox;

    QPushButton *ok;
    QPushButton *cancel;
    QPushButton *geomBrowseButton;
    gfxDisplay *vtkWidget;

  private slots:
    void browseClicked();
};
#endif
