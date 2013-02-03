#include <QtGui>
#include <math.h>

#include "gfxDisplay.h"
#include "gfxObject.h"

gfxDisplay::gfxDisplay(QVTKWidget *parent) : QVTKWidget(parent){
  int i;
  setAutoFillBackground(false);

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

  Scenery = new gfxObject(renderer);
  runRenderer();
}

void gfxDisplay::runRenderer(){
  printf("Requesting Render\n");
//  GetInteractor()->CreateTimer(0);
//  GetRenderWindow()->Render();
}

void gfxDisplay::loadScenery(QString filename){
  Scenery->loadCAD(filename);
}

int gfxDisplay::loadModel(QString filename){
  model.append(new gfxObject(renderer));
  model.back()->loadCAD(filename);
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