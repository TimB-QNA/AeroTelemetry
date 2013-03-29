#ifndef navigationToolbar_H
  #define navigationToolbar_H

#include <QtGui>
#include "telemetryData.h"
/*!
 * Enables navigation of dataset by time. Default display is in UTC
 */
class navigationToolbar : public QObject
{
  Q_OBJECT

  public:
    navigationToolbar(QToolBar *parent=0);

    void setMasterData(telemetryData *data);
    int timeIndex();
    QDateTime time();

  private:
    QPushButton *back;
    QPushButton *stepBack;
    QPushButton *stop;
    QPushButton *stepForward;
    QPushButton *forward;

    
    QPushButton *divTwo;
    QPushButton *timesTwo;
    QPushButton *normalSpeed;
    QPushButton *liveFeed;
    QSlider *streamPosition;

    QLabel *timeDisplay;
    
    QToolBar *toolBar;

    int timeIdx;
    telemetryData *masterData;
    telemetryData defaultTelemetry;

  private slots:
    void updateIndex();

  signals:
    void timeIndexChanged(int index);
};

#endif

