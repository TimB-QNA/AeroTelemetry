#ifndef gfxOSMnode_H
  #define gfxOSMnode_H

#include <qdom.h>
#include <stdlib.h>
#include "odPoint.h"
/*!\brief Handle nodes from OpenStreetMap
 *
 * This class handles individual nodes from OpenStreetmap.
 */
class gfxOSMnode {
  public:
    int ref;                                    ///< The OpenStreetMap node reference (the nodes get re-referenced for speed once loaded)
    double lat;                                 ///< Latitude of point
    double lon;                                 ///< Longitude of point
    odPoint plt;                                ///< Projected location for plotting
    bool isPlace;                               ///< Flag to define a place.
    QString name;                               ///< Name of place if isPlace is true.

    gfxOSMnode();
    void read(QDomNode n);
    void list();
    void writeXML(FILE *stream);
};

#endif
