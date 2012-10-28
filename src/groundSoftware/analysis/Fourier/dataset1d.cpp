#include "dataset1d.h"

dataset1d::dataset1d(){
}

dataset1d::dataset1d(int size){
  if (size<0) size=0;
  value.resize(size);
}
