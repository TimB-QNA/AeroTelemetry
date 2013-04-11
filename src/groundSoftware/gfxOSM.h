#ifndef gfxOSM_H
  #define gfxOSM_H

#include "gfxObject.h"
#include "gfxOSMnode.h"
#include "gfxOSMway.h"

#include <QtGui>
#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkTriangle.h>
#include <vtkQuad.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyLine.h>

#include <vector>
using namespace std;

class gfxOSM : public gfxObject
{
  public:
    gfxOSM(vtkRenderer *ren);
    bool loadCAD(QString filename);

  private:
    vtkActor* createActor(int obj);
    void simplifyrefs();
    
    QList<gfxOSMnode> node;
    QList<gfxOSMway> way;
};

#endif

