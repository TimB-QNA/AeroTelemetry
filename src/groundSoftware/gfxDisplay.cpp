#include <QtGui>
#include <math.h>

#include "gfxDisplay.h"

#include "gfxRhino3D.h"
#include "gfxOSM.h"

gfxDisplay::gfxDisplay(QVTKWidget *parent) : QVTKWidget(parent){
  int i;
  setAutoFillBackground(false);
  setBaseSize(640,480);
  
  // Setup renderer
  renderer = vtkRenderer::New();
  renderer->SetBackground(0.0,0.0,0.0);
  renderer->ResetCamera();
  
  GetRenderWindow()->AddRenderer(renderer);
  GetRenderWindow()->ReportGraphicErrorsOn();
  
  defaultCamera = vtkCamera::New();
  defaultCamera->SetPosition(10000,10000,10000);
  defaultCamera->SetFocalPoint(0,0,0);
  defaultCamera->SetViewUp(0,0,1);
  renderer->SetActiveCamera(defaultCamera);

  runRenderer();
}

void gfxDisplay::runRenderer(){
  printf("Requesting Render\n");
//  GetInteractor()->CreateTimer(0);
//  GetRenderWindow()->Render();
}

void gfxDisplay::loadScenery(QString filename){
  gfxRhino3D *tempR3D; tempR3D = new gfxRhino3D(renderer);
  gfxOSM     *tempOSM; tempOSM = new gfxOSM(renderer);
  
  if (tempR3D->loadCAD(filename)){
    Scenery = tempR3D;
    return;
  }else{
    delete tempR3D;
  }

  if (tempOSM->loadCAD(filename)){
    Scenery = tempOSM;
    return;
  }else{
    delete tempOSM;
  }
}

int gfxDisplay::loadModel(QString filename){
  gfxRhino3D *tempR3D; tempR3D = new gfxRhino3D(renderer);

  if (tempR3D->loadCAD(filename)){
    model.append(tempR3D);
  }else{
    delete tempR3D;
  }

  return model.size()-1;
}

void gfxDisplay::setCamera(viewSettings viewInfo){
  renderer->SetActiveCamera(viewInfo.camera);
  GetRenderWindow()->Render();
  update();
}

/*
void gfxDisplay::paintEvent(QPaintEvent* event){
  printf("Paint Event\n");
  if (!this->cachedImageCleanFlag){
    vtkRenderWindowInteractor* iren = NULL;
    if (this->mRenWin) iren = mRenWin->GetInteractor();
    if(!iren || !iren->GetEnabled()) return;
    iren->Render();
  }

  QPainter painter(this);
  painter.eraseRect( event->rect() );
  painter.drawPixmap(0, 0, cachedImage);
}
*/