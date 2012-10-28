#include "dataset2d.h"
#include <vector>
#include <string>
#include <fftw3.h>
using namespace std;

#ifndef FOURIER_H
  #define FOURIER_H
class fourier{
  public:
    void createTransform(dataset2d data, bool forward=true);
    dataset2d executeTransform(bool rawData=false);
    void destroyTransform();

  private:
    int npoints;
    double sampleRate;
    double *in;
    fftw_complex *out;
    fftw_plan plan;
};
#endif
