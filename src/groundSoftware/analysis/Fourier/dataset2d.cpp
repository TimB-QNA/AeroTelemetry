#include "dataset2d.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void dataset2d::createSampleData(){
  int i;
  double t, val, pi=4.*atan(1.);
  dataset1d tempRow(2);

  clear();
  title="Sample Dataset";
  columnName.push_back("Time");
  columnName.push_back("Value");

  for (t=0;t<10;t+=.01){
    tempRow.value[0]=t;
    tempRow.value[1]=0; //.5*rand()/(double)RAND_MAX;
    for (i=1;i<50;i++){
      tempRow.value[1]+=3./(double)i*cos((double)i*t*(2.*pi));
    }
    for (i=1;i<50;i++){
      tempRow.value[1]+=3./((double)i+.5)*sin(((double)i+.5)*t*(2.*pi));
    }
    row.push_back(tempRow);
  }
}

void dataset2d::plotData(){
  int i, j;
  FILE *script;

  script=fopen("/tmp/gplt.scr","w");

  fprintf(script,"set title \"%s\"\n",title.c_str());
  fprintf(script,"set xlabel \"%s\"\n",columnName[0].c_str());
  fprintf(script,"set ylabel \"%s\"\n",columnName[1].c_str());
  fprintf(script,"set grid\n");

  fprintf(script,"plot '-' with lines title '%s'",columnName[1].c_str());
  for (i=2;i<(int)row[0].value.size();i++){
    fprintf(script,", '-' with lines title '%s'",columnName[i].c_str());
  }
  fprintf(script,"\n");
  for (j=1;j<(int)row[0].value.size();j++){
    for (i=0;i<(int)row.size();i++){
      fprintf(script,"%lf\t%lf\n",row[i].value[0], row[i].value[j]);
    }
    fprintf(script,"e\n");
  }
  fprintf(script,"pause -1\n");
  fprintf(script,"quit\n");
  fclose(script);
  system("gnuplot /tmp/gplt.scr");
//  system("rm /tmp/gplt.scr");
}

void dataset2d::clear(){
  title="";
  row.clear();
  columnName.clear();
}