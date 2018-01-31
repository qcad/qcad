/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#ifndef RSPATIALINDEXSIMPLE_H
#define RSPATIALINDEXSIMPLE_H

#include "core_global.h"

#include <QSet>
#include <QList>

#include "RSpatialIndex.h"
#include "RDebug.h"
#include "RMath.h"



/**
 * \brief Simple spatial index implementation.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RSpatialIndexSimple: public RSpatialIndex {
public:
    RSpatialIndexSimple();
    virtual ~RSpatialIndexSimple();

    virtual RSpatialIndex* create();
    virtual void clear();

    /**
     * \nonscriptable
     */
    virtual void addToIndex(
        int id, int pos,
        double x1, double y1, double z1,
        double x2, double y2, double z2
    );

    //virtual void removeFromIndex(int id);
    virtual bool removeFromIndex(
            int id, int pos,
            double x1, double y1, double z1,
            double x2, double y2, double z2);

    virtual bool removeFromIndex(int id, const QList<RBox>& bb);

    virtual QMap<int, QSet<int> > queryIntersected(
        double x1, double y1, double z1,
        double x2, double y2, double z2,
        RSpatialIndexVisitor* dataVisitor=NULL
    );

    virtual QMap<int, QSet<int> > queryContained(
        double x1, double y1, double z1,
        double x2, double y2, double z2,
        RSpatialIndexVisitor* dataVisitor=NULL
    );

    virtual QMap<int, QSet<int> > queryNearestNeighbor(
        uint k,
        double x, double y, double z,
        RSpatialIndexVisitor* dataVisitor=NULL
    );

protected:
    //QMultiHash<RBox, int> si;
    QMap<int, QList<RBox> > si;
};

//QDebug operator<<(QDebug dbg, RSpatialIndexSimple& si);

Q_DECLARE_METATYPE(RSpatialIndexSimple*)

#endif
