#include "projection.h"
#include <math.h>

projection::projection(){
  polar=6356752.3;  // radius in meters
  equatorial=6378137.; // radius in meters
  pi=4.*atan(1.);
  projMethod=spherical;
}

odPoint projection::project(double longitude, double latitude, double altitude){
  return project(odPoint(longitude, latitude, altitude));
}

odPoint projection::project(odPoint llaPos){
  if (projMethod==spherical) return projectSpherical(llaPos);
  return llaPos;
}

/*!
 * Projects a point (Lat/Lon) to a point on a sphere.
 * This mechanism is much quicker than the ellipsoidal method, and achieves very similar results (for our purposes).
 */
odPoint projection::projectSpherical(odPoint llaPos){
  odPoint result;
  double r=(polar+equatorial)/2+llaPos.z;

  result.x=r*sin(llaPos.x*pi/180.);
  result.y=r*cos(llaPos.x*pi/180.);
  result.z=r*sin(llaPos.y*pi/180.);
  return result;
}

