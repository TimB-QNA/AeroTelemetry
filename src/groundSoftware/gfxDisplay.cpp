#include <QtGui>
#include <math.h>

#include "gfxDisplay.h"

#include "gfxOSM.h"

gfxDisplay::gfxDisplay(QVTKWidget *parent) : QVTKWidget(parent){
  int i;
  
  setAutoFillBackground(false);
  setBaseSize(640,480);
  
  // Setup renderer
  renderer = vtkRenderer::New();
  setBackground(QColor(0,0,0));
  renderer->ResetCamera();
  
  GetRenderWindow()->AddRenderer(renderer);
  GetRenderWindow()->ReportGraphicErrorsOn();
  
  defaultCamera = vtkCamera::New();
  defaultCamera->SetPosition(10000,10000,10000);
  defaultCamera->SetFocalPoint(0,0,0);
  defaultCamera->SetViewUp(0,0,1);
  renderer->SetActiveCamera(defaultCamera);

  GetInteractor()->StartListening();
}

void gfxDisplay::setBackground(QColor bckColour){
  renderer->SetBackground((float)bckColour.red()/255.,(float)bckColour.green()/255.,(float)bckColour.blue()/255.);
}

void gfxDisplay::loadScenery(QString filename){
  gfxObject *tmpObj;
  tmpObj = new gfxObject(renderer);
  if (tmpObj->loadCAD(filename)){
    Scenery=tmpObj;
  }else{
    delete tmpObj;
  }
}


int gfxDisplay::loadModel(QString filename){
  gfxObject *tmpObj;
  tmpObj = new gfxObject(renderer);
  if (tmpObj->loadCAD(filename)){
    model.append(tmpObj);
  }else{
    delete tmpObj;
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

void gfxDisplay::clear(){
  int i;
  /*
  delete Scenery;
  for (i=0;i<model.count();i++){
    delete model[i];
  }
  model.clear();
  */
}