#include <QtGui>
#include <math.h>

#include "gfxRhino3D.h"

gfxRhino3D::gfxRhino3D(vtkRenderer *ren) : gfxObject(ren) {
}

bool gfxRhino3D::loadCAD(QString filename){
  int i, layer;
  ON_Color objCol;
     
  //Load geometry...
  if (filename.endsWith(".3dm")){
    load3dm(filename);
    for (i=0;i<model.m_object_table.Count();i++){   
      if (ON::color_from_object == model.m_object_table[i].m_attributes.ColorSource()){
        objCol=model.m_object_table[i].m_attributes.m_color; 
      }else{
        layer=model.m_object_table[i].m_attributes.m_layer_index;
        objCol=model.m_layer_table[layer].Color();
      }
      actor.push_back( createActor(model.m_object_table[i].m_object, objCol.FractionRed(), objCol.FractionGreen(), objCol.FractionBlue()) );
    }
  }
  for (i=0;i<actor.size();i++) renderer->AddActor(actor[i]);
  return true;
}


vtkActor* gfxRhino3D::createActor(const ON_Object *object, double red, double green, double blue){
  ON_Brep *brep;
  ON_SimpleArray<const ON_Mesh*> cmsh;
  int i, j, k, l, npts;
  double x1,x2,x3,x4, y1,y2,y3,y4, z1,z2,z3,z4;
  
  // Add Meshes to list
  points = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> list = vtkSmartPointer<vtkCellArray>::New();
   
  brep=0;
  brep = (ON_Brep*)ON_Brep::Cast(object);
  if (brep){
    brep->GetMesh(ON::render_mesh, cmsh);
    if (cmsh.Count()>0){
      for (l=0;l<cmsh.Count();l++){
        npts=points->GetNumberOfPoints();
        for (j=0;j<cmsh[l]->m_V.Count();j++) points->InsertNextPoint(cmsh[l]->m_V[j].x, cmsh[l]->m_V[j].y, cmsh[l]->m_V[j].z);
        for (j=0;j<cmsh[l]->m_F.Count();j++){  
          if (cmsh[l]->m_F[j].IsTriangle()){
            vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
            for (k=0;k<3;k++) triangle->GetPointIds()->SetId(k,cmsh[l]->m_F[j].vi[k]+npts);
            list->InsertNextCell(triangle);
          }else{
            vtkSmartPointer<vtkQuad> quad = vtkSmartPointer<vtkQuad>::New();
            for (k=0;k<4;k++) quad->GetPointIds()->SetId(k,cmsh[l]->m_F[j].vi[k]+npts);
            list->InsertNextCell(quad);
          }
        }
      }
    }
  }
  
  //Create a polydata object and add data
  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetPolys(list);
  
  //Create Mapper
  vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
  mapper->SetInput(polydata);
  mapper->SetScalarRange(0.,1.);
  
  //Create Actor
  vtkActor *tmpActor = vtkActor::New();
  tmpActor->SetMapper(mapper);
  tmpActor->GetProperty()->SetColor(red, green, blue);
  return tmpActor;  
}


int gfxRhino3D::load3dm(QString inputFile){
  int i, j;
  ON_TextLog dump_to_stdout;
  ON_TextLog* dump = &dump_to_stdout;
  bool ok;  
  FILE *infile;
  char line[4096];
  
  int cld=0, pnt=0, crv=0, srf=0, brp=0, msh=0;
  ON_PointCloud *cloud;
  ON_Point *point;
  ON_Curve *curve;
  ON_Surface *surface;
  ON_Brep *brep;
  ON_Mesh *mesh;
  
  // If type is 3dm, handle with OpenNURBS Toolkit...
//  dump->Print("\nOpenNURBS Archive File:  %s\n", inputFile.toAscii().data());
  // open file containing opennurbs archive
  infile = ON::OpenFile( inputFile.toAscii().data(), "rb");
  if ( !infile ) return 2;
  
  // create achive object from file pointer
  ON_BinaryFile archive( ON::read3dm, infile );
  // read the contents of the file into "model"
  bool rc = model.Read( archive, dump );
  // close the file
  ON::CloseFile( infile );
//  if (rc) printf("Read file sucessfully\n");
//  if (model.IsValid(dump)) printf("Model is Valid\n");
  
  // Here we attempt to cast objects and report the results... 
  for (i=0;i<model.m_object_table.Count();i++){
    cloud = (ON_PointCloud*)ON_PointCloud::Cast(model.m_object_table[i].m_object);
    if (cloud) cld++;
    point = (ON_Point*)ON_Point::Cast(model.m_object_table[i].m_object);
    if (point) pnt++;
    curve = (ON_Curve*)ON_Curve::Cast(model.m_object_table[i].m_object);
    if (curve) crv++;
    surface = (ON_Surface*)ON_Surface::Cast(model.m_object_table[i].m_object);
    if (surface) srf++;
    brep = (ON_Brep*)ON_Brep::Cast(model.m_object_table[i].m_object);
    if (brep) brp++;
    mesh = (ON_Mesh*)ON_Mesh::Cast(model.m_object_table[i].m_object);
    if (mesh) msh++;  
  }
/*
  printf("Model Contains:\n");
  printf("  %i Layers\n",model.m_layer_table.Count());
  printf("  %i Meshes\n",msh);
  printf("  %i Breps\n",brp);
  printf("  %i Surfaces\n",srf);
  printf("  %i Curves\n",crv);
  printf("  %i Points\n",pnt);
  printf("  %i Point Clouds\n",cld);
  
  printf("The following Layers are visible and will be meshed:\n");
  for (i=0;i<model.m_layer_table.Count();i++){
    if (model.m_layer_table[i].IsVisible()) printf("  %s\n",convertONstring(model.m_layer_table[i].LayerName()).toAscii().data());
  }
  */
}

int gfxRhino3D::findONLayer(QString LayerName){
  int j;
  for (j=0;j<model.m_layer_table.Count();j++){
    if (LayerName==convertONstring(model.m_layer_table[j].LayerName())) return j;
  }
  return -1;
}

QString gfxRhino3D::convertONstring(ON_wString ONs){
  int j;
  QString line;
  line="";
  for (j=0;j<ONs.Length();j++){
    line+=ONs[j];
  }
  return line;
}
