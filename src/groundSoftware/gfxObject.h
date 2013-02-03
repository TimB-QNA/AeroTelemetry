#ifndef gfxObject_H
  #define gfxObject_H

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

class gfxObject
{
  public:
    vector<vtkActor*> actor;
    
    gfxObject(vtkRenderer *ren);
    void loadCAD(QString filename);

  public:
    void setPosition(double x, double y, double z);
    void setRotation(double x, double y, double z);
    void addUserSphere(double x, double y, double z, double r, float red=1, float green=0, float blue=0);
    
  private:
    vtkRenderer *renderer;
    vtkActor* createActor(const ON_Object *object, double red, double green, double blue);
    
    int findONLayer(QString LayerName);
    QString convertONstring(ON_wString ONs);

    vtkSmartPointer<vtkPoints> points;
    ONX_Model model;
    int load3dm(QString inputFile);
};

#endif

