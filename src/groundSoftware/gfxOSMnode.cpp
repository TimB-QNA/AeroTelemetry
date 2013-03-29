#include <stdio.h>
#include <qdom.h>
#include "gfxOSMnode.h"

/*!
 * Standard initialisation to ensure that all nodes start life as simple nodes, not places!!
 */
gfxOSMnode::gfxOSMnode(){
  isPlace=false;
}

/*!
 * Load a node from an OpenStreetmap XML file.
 */
void gfxOSMnode::read(QDomNode n){
  QDomElement e;
  e=n.toElement();

  ref=e.attribute("id").toInt();
  lat=e.attribute("lat").toDouble();
  lon=e.attribute("lon").toDouble();
  if (e.attribute("k").toLower()=="place") isPlace=true;
  if (e.attribute("k").toLower()=="name") name=e.attribute("v");
}

/*!
 * Print all data related to this node.
 */
void gfxOSMnode::list(){
  printf("ID  = %i\n",ref);
  printf("Position: Lat = %lf deg       Lon = %lf deg\n",lat,lon);
  if (isPlace) printf("Place? Yes\n");
  if (!isPlace) printf("Place? No\n");
  printf("Name: %s\n",name.toAscii().data());
}

/*!
 * Write the node id, latitude and longitude data into an XML entry.
 */
void gfxOSMnode::writeXML(FILE *stream){
  fprintf(stream,"<node id=\"%i\" lat=\"%lf\" lon=\"%lf\" visible=\"true\">\n",ref,lat,lon);
  fprintf(stream,"  <tag k=\"created_by\" v=\"AeroTelemetry\"/>\n");
  fprintf(stream,"</node>\n");
}
