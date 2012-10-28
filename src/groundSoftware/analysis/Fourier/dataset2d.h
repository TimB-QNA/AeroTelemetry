#include "dataset1d.h"
#include <vector>
#include <string>
using namespace std;

#ifndef DS2D
  #define DS2D
class dataset2d{
  public:
    vector<dataset1d> row;
    vector<string> columnName;
    string title;

    void createSampleData();
    void plotData();
    void clear();
};
#endif
