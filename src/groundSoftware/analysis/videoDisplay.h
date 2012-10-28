#ifndef videoDisplay_H
  #define videoDisplay_H

#include <QtGui>

class videoDisplay : public QWidget
{
   Q_OBJECT

  public:
    videoDisplay(QWidget *parent=0);
       
  private:
    QImage        frameImg;
    
    void paintEvent(QPaintEvent *event);

  public slots:
    void updateFrame(QImage *img);
};

#endif

