#ifndef projection_H
  #define projection_H

  #include "odPoint.h"

class projection
{
  public:
    enum projectionType {none, spherical};
    projectionType projMethod;
    
    projection();
    odPoint project(double longitude, double latitude, double altitude=0);
    odPoint project(odPoint llaPos);

  private:
    odPoint projectNone(odPoint llaPos);
    odPoint projectSpherical(odPoint llaPos);

    double polar;
    double equatorial;
    double pi;
};

#endif
