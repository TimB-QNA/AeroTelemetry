#include <QtGui>
#include <math.h>

#include "gfxObject.h"

#include <vtkTextMapper.h>

gfxObject::gfxObject(vtkRenderer *ren){
  renderer=ren;
}


bool gfxObject::loadCAD(QString filename){
  return false;
}

void gfxObject::setPosition(double x, double y, double z){
  int i;
  for (i=0;i<(int)actor.size();i++){
    actor[i]->SetPosition(x,y,z);
  }
}

void gfxObject::setRotation(double x, double y, double z){
  int i;
  for (i=0;i<(int)actor.size();i++){
    actor[i]->SetOrientation(x,y,z);
  }
}

void gfxObject::addUserSphere(double x, double y, double z, double r, float red, float green, float blue){
  // Draw sphere at location and add to actor.
  vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetThetaResolution(15);
  sphere->SetPhiResolution(15);
  sphere->SetCenter(x,y,z);
  sphere->SetRadius(r);
    
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputConnection(sphere->GetOutputPort());
   
  vtkSmartPointer<vtkActor> sphere1 = vtkSmartPointer<vtkActor>::New();
  sphere1->SetMapper(sphereMapper);
  sphere1->GetProperty()->SetColor(red, green, blue);

  actor.push_back( sphere1 );
  renderer->AddActor(actor[actor.size()-1]);
}