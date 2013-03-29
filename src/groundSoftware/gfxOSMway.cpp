#include <stdio.h>
#include <qdom.h>
#include "gfxOSMway.h"

/*!
 * Initialises the way to be visible.
 */
gfxOSMway::gfxOSMway(){
}

/*!
 * Loads all data associated with the node from an OSM XML file.
 */
void gfxOSMway::read(QDomNode n){
  int nrc, ncount;
  QDomNode n2;
  QDomElement e;
  e=n.toElement();
  ref=e.attribute("id").toInt();

  // Count number of nodes along way...
  ncount=0;
  n2=n.firstChild();
  while (!n2.isNull()){
    e=n2.toElement();
    if (e.tagName()=="nd") ncount++;
    n2=n2.nextSibling();
  }
  nodes.assign(ncount, 0);

  n2=n.firstChild();
  nrc=0;
  while (!n2.isNull()){
    e=n2.toElement();
    if (e.tagName().toLower() == "nd"){
      nodes[nrc]=e.attribute("ref").toInt();
      nrc++;
    }
    if (e.tagName().toLower() == "tag"){
      if (e.attribute("k").toLower()=="highway"){
        type="highway";
        level=e.attribute("v").toLower();
      }
      if (e.attribute("k").toLower()=="waterway"){
        type="waterway";
        level=e.attribute("v").toLower();
      }
      if (e.attribute("k").toLower()=="area") type="area";

      if (e.attribute("k").toLower()=="leisure"){
        level=e.attribute("v").toLower();
        if (level=="pitch") type="area";
        if (level=="park") type="area";
      }

      if (e.attribute("k").toLower()=="building") level="building";
      if (e.attribute("k").toLower()=="parking") level="parking";
      if (e.attribute("k").toLower()=="name") name=e.attribute("v");
    }
    n2=n2.nextSibling();
  }
}

/*!
 * Lists details about this way. Eg. Type, level, name, etc.
 */
void gfxOSMway::list(){
  printf("Way Contains %i Nodes\n", nodes.size());
  printf("     ID = %i\n",ref);
  printf("   Type = %s\n",type.toAscii().data());
  printf("  Level = %s\n",level.toAscii().data());
  printf("   Name = %s\n",name.toAscii().data());
  if (visible)  printf("Visible = true\n");
  if (!visible) printf("Visible = false\n");
}

/*!
 * List of node numbers for this way (for debugging purposes).
 */
void gfxOSMway::listNodes(){
  int i;
  printf("Way Contains %i Nodes\n", nodes.size());
  printf("Nodes follow:\n");
  for (i=0;i<nodes.size();i++) printf("%i\n", nodes[i]);
}

/*!
 * Not yet written. However, it should dump all the way data in XML format.
 */
void gfxOSMway::writeXML(FILE *stream){
  /*
    <way id="26923997" visible="true" timestamp="2008-09-08T11:28:24+01:00" user="Mappo">
    <nd ref="295017897"/>
    <nd ref="295017902"/>
    <nd ref="295017903"/>
    <nd ref="295017904"/>
    <nd ref="295017905"/>
    <nd ref="295017906"/>
    <tag k="created_by" v="Potlatch 0.10b"/>
    <tag k="highway" v="residential"/>
  </way>
  */

}