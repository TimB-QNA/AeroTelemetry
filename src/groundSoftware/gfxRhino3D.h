#ifndef gfxRhino3D_H
  #define gfxRhino3D_H

#include "gfxObject.h"
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
#include <vector>
#include "openNURBS-5/opennurbs.h"
using namespace std;

class gfxRhino3D : public gfxObject
{
  public:
    gfxRhino3D(vtkRenderer *ren);
    bool loadCAD(QString filename);

  private:
    vtkActor* createActor(const ON_Object *object, double red, double green, double blue);
    
    int findONLayer(QString LayerName);
    QString convertONstring(ON_wString ONs);

    ONX_Model model;
    int load3dm(QString inputFile);
};

#endif

