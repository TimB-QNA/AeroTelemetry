// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>
#include "videoDisplay.h"

videoDisplay::videoDisplay(QWidget *parent) : QWidget(parent){
  frameImg = QImage(640,480,QImage::Format_RGB888);
  frameImg.fill(QColor(0,0,0));
}

void videoDisplay::paintEvent(QPaintEvent *event){
  char string[20];
  QPainter painter;

  if (!painter.begin(this)) return;

  painter.fillRect(rect(), QColor(0,0,0));
  painter.drawImage( rect(), frameImg );
}

void videoDisplay::updateFrame(QImage *img){
  frameImg=img->copy(img->rect());
  update();
}
