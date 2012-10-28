#include <vector>
using namespace std;

#ifndef DS1D
  #define DS1D
class dataset1d{
  public:
    vector<double> value;

    dataset1d();
    dataset1d(int size);
};
#endif
