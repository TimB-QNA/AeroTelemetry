#ifndef gfxOSMway_H
  #define gfxOSMway_H

#include <qdom.h>
#include <vector>
using namespace std;


/*!\brief Handle ways for OpenStreetMap
 * 
 * OpenStreetmap defines roads, paths and areas as curves (defining or perimeter).
 * However, since many ways share points, OSM stores nodes separately to ways.
 * The node-numbers are then referenced to produce the required feature.
 */
class gfxOSMway
{
  public:
    int ref;                                    ///< OSM way reference.
    vector<int> nodes;                          ///< List of nodes in this way.
    QString type;                               ///< Type of way. ie. highway, waterway, area etc.
    QString level;                              ///< Classification of the way. ie. primary/secondary
    QString name;                               ///< Name of the way.
    bool visible;                               ///< Controls whether this way is plotted.

    gfxOSMway();
    void read(QDomNode n);
    void list();
    void listNodes();
    void writeXML(FILE *stream);
};

#endif
