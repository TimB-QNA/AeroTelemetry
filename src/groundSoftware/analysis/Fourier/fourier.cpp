#include "fourier.h"
#include <math.h>

void fourier::createTransform(dataset2d data, bool forward){
  int i;

  printf("Fourier :: Allocating memory\n");
  npoints=data.row.size();
  in= (double *)fftw_malloc(npoints*sizeof(double));
  if (in == NULL){
    printf("Fourier :: Failed to allocate memory for input\n");
    return;
  }

  out= (fftw_complex *)fftw_malloc(npoints*sizeof(fftw_complex));
  if (out == NULL){
    fftw_free(in);
    printf("Fourier :: Failed to allocate memory for output\n");
    return;
  }
  printf("Fourier :: Creating transform plan\n");
  plan=fftw_plan_dft_r2c_1d(npoints, in, out, FFTW_ESTIMATE);
//  plan=fftw_plan_r2r_1d(npoints, in, out, FFTW_DHT, FFTW_FORWARD);
//  if (!forward) p=fftw_plan_r2r_1d(npoints, in, out, FFTW_DHT, FFTW_BACKWARD);
  if (plan == NULL){
    destroyTransform();
    printf("Fourier :: Failed to create transform plan\n");
    return;
  }

  printf("Fourier :: Setting sample rate\n");
  sampleRate=npoints/(data.row[npoints-1].value[0] - data.row[0].value[0]);

//  printf("Fourier :: Copying data\n");
  for (i=0;i<npoints;i++){
    in[i]=data.row[i].value[1];
    out[i][0]=0.; out[i][1]=0.;
  }
}

dataset2d fourier::executeTransform(bool rawData){
  int i, imax=npoints;
  dataset2d rds;
  dataset1d row(3);

  if (plan == NULL){
    destroyTransform();
    printf("Fourier :: Attempt to execute transform with invalid plan\n");
    return rds;
  }

  fftw_execute(plan);

  if (!rawData) imax=npoints/2+1;

  for (i=0;i<imax;i++){
    row.value[0]=(double)i*sampleRate/(double)npoints;
    if (!rawData){
      row.value[1]=2.*fabs(out[i][0]/(double)npoints);
      row.value[2]=2.*fabs(out[i][1]/(double)npoints);
    }else{
      row.value[1]=out[i][0];
      row.value[2]=out[i][1];
    }
    rds.row.push_back(row);
  }

  rds.title="Fourier Transform";
  rds.columnName.push_back("Frequency (Hz)");
  rds.columnName.push_back("Transform[0]");
  rds.columnName.push_back("Transform[1]");
}

void fourier::destroyTransform(){
  fftw_destroy_plan(plan);
  npoints=0;
  fftw_free(in);
  fftw_free(out);
}
