#include <QtGui>
#include <math.h>

#include "gfxOSM.h"
#include "projection.h"

extern projection planet;

gfxOSM::gfxOSM(vtkRenderer *ren) : gfxObject(ren) {
}

bool gfxOSM::loadCAD(QString filename){
  QDomElement root;
  QDomNode xmlNode, node2;
  QDomElement element, element2;
  gfxOSMnode tmpnode;
  gfxOSMway  tmpway;
  int i;
  QString errMsg;
  int erl, erc;
  bool isdup;

  QFileInfo fi(filename);

  QFile file;
  file.setFileName(filename);
  if (!file.open( QIODevice::ReadOnly )){
    printf("OSMloader :: Could not open file\n");
    return false;
  }

  QDomDocument doc( "OSMFile" );
  if (!doc.setContent( &file, false, &errMsg, &erl, &erc)){
    printf("OSMloader :: Failed to set content\n");
    printf("OSMloader :: At line %i, Column %i\n", erl, erc);
    printf("OSMloader :: QDomDocument returned - %s\n",errMsg.toAscii().data());
    file.close();
    return false;
  }
  file.close();

  printf("OSMloader :: File loaded into memory\n");

  root=doc.documentElement();

  if (root.tagName() != "osm"){
    printf("OSMloader :: This is not an OpenStreetMap XML file\n");
    return false;
  }

  // Useful Info
  printf("OSMloader ::     Filesize = %7.3lf MB\n",(double)fi.size()/(1024.*1024.));
  printf("OSMloader ::      Version = %s\n",root.attribute( "version" ).toAscii().data());
  printf("OSMloader :: Created With = %s\n",root.attribute( "generator" ).toAscii().data());

  xmlNode=root.firstChild();
  node.clear();
  way.clear();

  xmlNode=root.firstChild();
  while (!xmlNode.isNull()){
    element=xmlNode.toElement();

    if (!element.isNull()){
      if (element.tagName()=="node"){
        tmpnode.read(xmlNode);
        isdup=false;
        for (i=0;i<(int)node.size();i++){
          if (tmpnode.ref==node[i].ref) isdup=true;
        }
        if (!isdup) node.push_back(tmpnode);
      }
      if (element.tagName()=="way"){
        tmpway.read(xmlNode);
        isdup=false;
        for (i=0;i<(int)way.size();i++){
          if (tmpnode.ref==way[i].ref) isdup=true;
        }
        if (!isdup) way.push_back(tmpway);
      }
    }
    xmlNode=xmlNode.nextSibling();
  }
  printf("OSMloader :: XML - Data Loaded, simplifying references\n");
  simplifyrefs();

  points = vtkSmartPointer<vtkPoints>::New();
  for (i=0;i<node.size();i++){
    node[i].plt=odPoint(node[i].lon, node[i].lat, 0);
 //   node[i].plt=planet.project(node[i].lon, node[i].lat);
 //   printf("Node position = %.2lf\t%.2lf\t%.2lf\n", node[i].plt.x, node[i].plt.y, node[i].plt.z);
    points->InsertNextPoint(node[i].plt.x, node[i].plt.y, node[i].plt.z);
  }
  
  for (i=0;i<way.size();i++){
    actor.push_back( createActor(i));
  }
  for (i=0;i<actor.size();i++) renderer->AddActor(actor[i]);
  
  return true;
}


vtkActor* gfxOSM::createActor(int obj){
//  ON_Brep *brep;
//  ON_SimpleArray<const ON_Mesh*> cmsh;
  int i, j, k, l, npts;
  vtkSmartPointer<vtkPolyLine> polyLine;
  vtkSmartPointer<vtkTriangle> triangle;
  vtkSmartPointer<vtkCellArray> lineCell = vtkSmartPointer<vtkCellArray>::New();
  vtkSmartPointer<vtkCellArray> polyCell = vtkSmartPointer<vtkCellArray>::New();

  if (way[obj].type.toLower()=="highway"){
    polyLine = vtkSmartPointer<vtkPolyLine>::New();
    polyLine->GetPointIds()->SetNumberOfIds(way[obj].nodes.size());
    for (i=0;i<way[obj].nodes.size();i++){
      if (way[obj].nodes[i]==way[obj].nodes.size()-1) way[obj].listNodes();
      polyLine->GetPointIds()->SetId(i,way[obj].nodes[i]);
    }
    lineCell->InsertNextCell(polyLine);
    
  }

  if (way[obj].type.toLower()=="area"){
    for (i=2;i<way[obj].nodes.size()-1;i++){
      triangle = vtkSmartPointer<vtkTriangle>::New();
      triangle->GetPointIds()->SetId(0,way[obj].nodes[0]);
      triangle->GetPointIds()->SetId(1,way[obj].nodes[i-1]);
      triangle->GetPointIds()->SetId(2,way[obj].nodes[i]);
      polyCell->InsertNextCell(triangle);
    }
  }

  
  //Create a polydata object and add data
  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetLines(lineCell);
  polydata->SetPolys(polyCell);
  //Create Mapper
  vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
  mapper->SetInput(polydata);
  mapper->SetScalarRange(0.,1.);
  
  //Create Actor
  vtkActor *tmpActor = vtkActor::New();
  tmpActor->SetMapper(mapper);
  if (way[obj].type.toLower()=="highway" && way[obj].level.toLower()=="motorway")  tmpActor->GetProperty()->SetColor(0, 0, 1);
  if (way[obj].type.toLower()=="highway" && way[obj].level.toLower()=="primary")   tmpActor->GetProperty()->SetColor(1, 0, 0);
  if (way[obj].type.toLower()=="highway" && way[obj].level.toLower()=="secondary") tmpActor->GetProperty()->SetColor(1, 0.5, 0);
  if (way[obj].type.toLower()=="highway" && way[obj].level.toLower()=="tertiary")  tmpActor->GetProperty()->SetColor(1, 1, 0);
  
  if (way[obj].type.toLower()=="area")     tmpActor->GetProperty()->SetColor(0, 0.5, 0);
  return tmpActor;  
}



/*!
 * This function renumbers the node references in each way to correspond to the node index as stored.
 */
void gfxOSM::simplifyrefs(){
  int i,j,k;
  for (i=0;i<(int)way.size();i++){
    for (j=0;j<way[i].nodes.size();j++){
      for (k=0;k<(int)node.size();k++){
        if (way[i].nodes[j]==node[k].ref){
          way[i].nodes[j]=k;
          break;
        }
      }
    }
  }
}
