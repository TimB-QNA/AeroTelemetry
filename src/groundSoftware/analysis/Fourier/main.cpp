#include "dataset2d.h"
#include "fourier.h"

int main(){
  dataset2d testData, result;
  fourier transform;

  // Populate dataset with arbitrary data
  testData.createSampleData();
  testData.plotData();

  // Create forward transform
  transform.createTransform(testData);
  result=transform.executeTransform();
  transform.destroyTransform();
  result.plotData();
}