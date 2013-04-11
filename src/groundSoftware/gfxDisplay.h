#ifndef gfxDisplay_H
  #define gfxDisplay_H

#include <QtGui>
#include <QVTKWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkTriangle.h>
#include <vtkQuad.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vector>

#include "gfxObject.h"
#include "viewSettings.h"
using namespace std;

class gfxDisplay : public QVTKWidget
{
   Q_OBJECT

  public:
    QList<gfxObject*> model;
    
    gfxDisplay(QVTKWidget *parent=0);
    void clear();
    void loadScenery(QString filename);
    int  loadModel(QString filename);
    void setCamera(viewSettings viewInfo);

    void setBackground(QColor bckColour);
    
  private slots:
//    void paintEvent(QPaintEvent* event);

  private:
  //  QVTKWidget *display;
    vtkSmartPointer<vtkCamera> defaultCamera;
    vtkSmartPointer<vtkRenderer> renderer;
    gfxObject *Scenery;
};

#endif

